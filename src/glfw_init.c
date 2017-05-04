/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glfw_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 20:31:30 by pmartine          #+#    #+#             */
/*   Updated: 2017/05/03 20:33:21 by yalaouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shaderpixel.h"
#include <math.h>

static t_vec2	g_angleamount;
static int		g_cursormode;
static float	g_lastpausedtime;
int				g_gl_ssnbr = 1;

#define KCC int a, int

static void		key_callback(GLFWwindow *g_window, int key, int scancode,
		KCC mods)
{
	(void)scancode;
	key_callback2(g_window, key, a, mods);
	if (key == GLFW_KEY_SPACE && a == GLFW_PRESS)
	{
		g_input_pause ^= a;
		if (g_input_pause)
			g_lastpausedtime = get_current_time();
		else
			g_paused_time += get_current_time() - g_lastpausedtime;
	}
	if (key == GLFW_KEY_C)
		g_cursormode ^= a == GLFW_PRESS;
	glfwSetInputMode(g_window, GLFW_CURSOR, (g_cursormode) ? \
		GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
	if (key == GLFW_KEY_P && a == GLFW_PRESS)
	{
		INIT(char *, name, (char *)malloc(sizeof(char) * 50));
		name = ft_strjoin(name, "screenshot_");
		name = ft_strjoin(name, ft_itoa(g_gl_ssnbr));
		name = ft_strjoin(name, ".png");
		SOIL_save_screenshot(name, SOIL_SAVE_TYPE_PNG, 0, 0, 1080, 720);
		free(name);
		g_gl_ssnbr++;
	}
}

static void		g_mouse_callback(GLFWwindow *win, double x, double y)
{
	(void)win;
	g_mouse.x = x;
	g_mouse.y = y;
	if (glfwGetInputMode(win, GLFW_CURSOR) == GLFW_CURSOR_DISABLED)
	{
		g_angleamount.x += ((g_window.x / 2.) - g_mouse.x) / 200;
		g_angleamount.y += ((g_window.y / 2.) - g_mouse.y) / 200;
		if (g_angleamount.y > 1.5f)
			g_angleamount.y = 1.5f;
		if (g_angleamount.y < -1.5f)
			g_angleamount.y = -1.5f;
		g_forward.x = cos(g_angleamount.y) * sin(g_angleamount.x);
		g_forward.y = sin(g_angleamount.y);
		g_forward.z = cos(g_angleamount.y) * cos(g_angleamount.x);
	}
}

static void		g_mouse_click_callback(GLFWwindow *win, int button, \
	int action, int mods)
{
	(void)win;
	(void)action;
	(void)mods;
	(void)button;
	if (action == 1)
		g_mouse.z = 1;
	else
		g_mouse.z = 0;
}

static void		resize_callback(GLFWwindow *win, int width, int height)
{
	(void)win;
	g_window.x = width;
	g_window.y = height;
}

GLFWwindow		*init(char *name)
{
	GLFWwindow *win;

	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
	{
		printf("glfwInit error !\n");
		exit(-1);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	if (!(win = glfwCreateWindow(WIN_W, WIN_H, name, NULL, NULL)))
	{
		printf("failed to create g_window !\n");
		exit(-1);
	}
	glfwSetKeyCallback(win, key_callback);
	glfwSetCursorPosCallback(win, g_mouse_callback);
	glfwSetMouseButtonCallback(win, g_mouse_click_callback);
	glfwSetWindowSizeCallback(win, resize_callback);
	glfwMakeContextCurrent(win);
	glfwSwapInterval(1);
	glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	return (win);
}
