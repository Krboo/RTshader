/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 23:30:02 by alelievr          #+#    #+#             */
/*   Updated: 2017/05/02 18:20:42 by pmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shaderpixel.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

#define FTN GLint *unis, GLint
#define FTN2 GLuint program, GLFWwindow *win, t_file *sources, size_t

static float g_last_paused_time;

t_vec4		g_mouse = {0, 0, 0, 0};
t_vec4		g_move = {0, 0, 0, 1};
t_vec2		g_window = {WIN_W, WIN_H};
t_vec3		g_forward = {0, 0, 1};
int			g_shadow = 0;
int			g_keys = 0;
int			g_input_pause = 0;
long		g_last_modified_file[0xF00] = {0};
float		g_paused_time = 0;
float		g_fov = 1.2;
float		g_ambient = 0.2;
t_selected	g_selected_object = {.dir_uniform = -1, .pos_uniform = -1};
int			g_selected_object_index = 0;

static void		usage(const char *n)
{
	printf("usage: %s <shader>\n", n);
	exit(0);
}

void			loop(GLFWwindow *win, GLuint program, GLuint vao, FTN *images)
{
	float	ratio;
	int		width;
	int		height;

	glfwGetFramebufferSize(win, &width, &height);
	ratio = width / (float)height;
	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT);
	update_keys();
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_TEXTURE_2D);
	update_uniforms(unis, images);
	glUseProgram(program);
	glBindVertexArray(vao);
	g_last_paused_time = get_current_time();
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 6);
	g_paused_time += get_current_time() - g_last_paused_time;
	glfwSwapBuffers(win);
	if (glfwGetInputMode(win, GLFW_CURSOR) == GLFW_CURSOR_DISABLED)
		glfwSetCursorPos(win, g_window.x / 2, g_window.y / 2);
	glfwPollEvents();
}

static void		load_scene_directory(char *scene_file)
{
	static char		path[1024];
	char			*off;

	if ((off = strrchr(scene_file, '/')))
	{
		strncpy(path, scene_file, off - scene_file);
		path[off - scene_file] = 0;
	}
	else
		strcpy(path, ".");
	strcat(path, "/");
	get_scene_directory(path);
}

static void		main_loop(GLint *images, GLint *unis, GLuint vao, FTN2 num)
{
	check_file_changed(&program, sources, num);
	if (!g_input_pause)
		update_object_transform();
	loop(win, program, vao, unis, images);
	display_window_fps(win);
}

int				main(int ac, char **av)
{
	static t_file	sources[0xF00];
	size_t			num;
	t_scene			scene;
	int				atlas_id;
	GLint			*unis;

	scene = (t_scene){.root_view = NULL};
	if (ac < 1)
		usage(*av);
	parse_rt_file(av[1], &scene);
	load_scene_directory(av[1]);
	get_scene(&scene);
	INIT(GLFWwindow *, win, init("Re Tweet"));
	INIT(char *, program_source, build_shader(&scene, get_scene_directory(NULL),
		&atlas_id, sources));
	init_source_file(sources, 0xF00, &num);
	INIT(GLuint, program, create_program(program_source, true));
	INIT(GLuint, vao, create_vao(create_vbo(), program));
	unis = get_uniform_location(program);
	INIT(GLint *, images, (int[]){atlas_id});
	get_program(program);
	while (!glfwWindowShouldClose(win))
		main_loop(images, unis, vao, program, win, sources, num);
	glfwTerminate();
	return (0);
}
