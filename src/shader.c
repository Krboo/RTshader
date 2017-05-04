/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 21:53:51 by pmartine          #+#    #+#             */
/*   Updated: 2017/05/03 21:57:34 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shaderpixel.h"
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>

static void		check_compilation(GLuint shader, bool fatal)
{
	GLint			is_compiled;
	GLint			max_length;
	char			buff[0xF000];

	is_compiled = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &is_compiled);
	if (is_compiled == GL_FALSE)
	{
		max_length = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &max_length);
		glGetShaderInfoLog(shader, max_length, &max_length, buff);
		printf("%s\n", buff);
		glDeleteShader(shader);
		if (fatal)
		{
			printf("shader compilation error, exiting\n");
			exit(-1);
		}
	}
}

static void		check_link(GLuint program, bool fatal)
{
	GLint			is_linked;
	GLint			max_length;
	char			buff[0xF000];

	is_linked = 0;
	glGetProgramiv(program, GL_LINK_STATUS, (int *)&is_linked);
	if (is_linked == GL_FALSE)
	{
		max_length = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &max_length);
		glGetProgramInfoLog(program, max_length, &max_length, buff);
		printf("%s\n", buff);
		glDeleteProgram(program);
		if (fatal)
		{
			printf("link error, exiting\n");
			exit(-1);
		}
	}
}

static GLuint	compile_shader_fragments(char *file, bool fatal)
{
	GLuint			ret;

	ret = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(ret, 1, (const GLchar *const *)&file, NULL);
	glCompileShader(ret);
	check_compilation(ret, fatal);
	return (ret);
}

static GLuint	compile_shader_vertex(bool fatal)
{
	GLuint			ret;

	ret = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(ret, 1, &g_vertex_shader_text, NULL);
	glCompileShader(ret);
	check_compilation(ret, fatal);
	return (ret);
}

GLuint			create_program(char *file, bool fatal)
{
	GLuint			program;
	const GLuint	shader_vertex = compile_shader_vertex(fatal);
	const GLuint	shader_fragment = compile_shader_fragments(file, fatal);

	if (shader_vertex == 0 || shader_fragment == 0)
		return (0);
	program = glCreateProgram();
	glAttachShader(program, shader_vertex);
	glAttachShader(program, shader_fragment);
	glLinkProgram(program);
	check_link(program, fatal);
	return (program);
}
