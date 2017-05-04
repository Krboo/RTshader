/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shaderutils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 10:43:59 by alelievr          #+#    #+#             */
/*   Updated: 2017/04/29 11:04:44 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shaderpixel.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

GLuint			create_vbo(void)
{
	const float	points[] = {
		-1.0f, -1.0f,
		-1.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, -1.0f,
		-1.0f, -1.0f,
	};
	GLuint		vbo;

	vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
	return (vbo);
}

GLuint			create_vao(GLuint vbo, int program)
{
	GLint		frag_pos;
	GLuint		vao;

	vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	frag_pos = glGetAttribLocation(program, "fragPosition");
	glEnableVertexAttribArray(frag_pos);
	glVertexAttribPointer(frag_pos, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2,
		(void *)0);
	return (vao);
}

void			check_file_changed(GLuint *program, t_file *files, size_t num)
{
	struct stat		st;
	size_t			i;
	int				fd;

	i = 0;
	while (i < num)
	{
		if (!FILE_CHECK_EXT(files[i].path, "glsl"))
			continue ;
		stat(files[i].path, &st);
		if (g_last_modified_file[files[i].fd] != st.st_mtime)
		{
			printf("file modified: %s\n", files[i].path);
			g_last_modified_file[files[i].fd] = st.st_mtime;
			close(files[i].fd);
			if ((fd = open(files[i].path, O_RDONLY)) != -1)
				files[i].fd = fd;
			else
				break ;
			recompile_program(files, program);
		}
		i++;
	}
}

void			recompile_program(t_file *files, GLuint *program)
{
	int				atlas_id;
	GLint			new_program;

	new_program = create_program(build_shader(get_scene(NULL),
				get_scene_directory(NULL), &atlas_id, files), false);
	if (new_program != 0)
	{
		glDeleteProgram(*program);
		*program = new_program;
		printf("shader reloaded !\n");
		get_uniform_location(*program);
	}
}

void			init_source_file(t_file *files, size_t max, size_t *num)
{
	struct stat		st;

	*num = 0;
	while (42)
	{
		if (*num >= max)
			break ;
		files[*num].fd = open(files[*num].path, O_RDONLY);
		if (stat(files[*num].path, &st) == -1)
			return ;
		g_last_modified_file[files[*num].fd] = st.st_mtime;
		if (!S_ISREG(st.st_mode) || !(st.st_mode & S_IRUSR))
		{
			printf("not a valid file: %s\n", files[*num].path);
			exit(-1);
		}
		else
			(*num)++;
	}
}
