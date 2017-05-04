/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glfw_init2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 20:39:03 by pmartine          #+#    #+#             */
/*   Updated: 2017/05/02 20:58:51 by pmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shaderpixel.h"
#include <math.h>

void		error_callback(int error, const char *description)
{
	(void)error;
	fprintf(stderr, "Error: %s\n", description);
}

void		key_callback3(GLFWwindow *g_window, int key, int a, int mods)
{
	(void)mods;
	(void)g_window;
	if (key == GLFW_KEY_X)
		BIT_SET(g_keys, SOBJ_DIR_X, a == GLFW_PRESS || a == GLFW_REPEAT);
	if (key == GLFW_KEY_Y)
		BIT_SET(g_keys, SOBJ_DIR_Y, a == GLFW_PRESS || a == GLFW_REPEAT);
	if (key == GLFW_KEY_Z)
		BIT_SET(g_keys, SOBJ_DIR_Z, a == GLFW_PRESS || a == GLFW_REPEAT);
	if (key == GLFW_KEY_KP_ADD || key == GLFW_KEY_EQUAL)
		BIT_SET(g_keys, PLUS, a == GLFW_PRESS || a == GLFW_REPEAT);
	if (key == GLFW_KEY_KP_SUBTRACT || key == GLFW_KEY_MINUS)
		BIT_SET(g_keys, MOIN, a == GLFW_PRESS || a == GLFW_REPEAT);
	if (key == GLFW_KEY_TAB && !(mods & GLFW_MOD_SHIFT) && a == GLFW_PRESS)
	{
		g_selected_object_index++;
		select_object();
	}
	if (key == GLFW_KEY_TAB && (mods & GLFW_MOD_SHIFT) && a == GLFW_PRESS)
	{
		g_selected_object_index--;
		select_object();
	}
	if (key == GLFW_KEY_O && a == GLFW_PRESS)
		g_shadow ^= a;
}

void		key_callback2(GLFWwindow *g_window, int key, int a, int mods)
{
	(void)mods;
	if (key == GLFW_KEY_ESCAPE && a == GLFW_PRESS)
		glfwSetWindowShouldClose(g_window, GLFW_TRUE);
	if (key == GLFW_KEY_RIGHT)
		BIT_SET(g_keys, RIGHT, a == GLFW_PRESS || a == GLFW_REPEAT);
	if (key == GLFW_KEY_LEFT)
		BIT_SET(g_keys, LEFT, a == GLFW_PRESS || a == GLFW_REPEAT);
	if (key == GLFW_KEY_UP)
		BIT_SET(g_keys, FORWARD, a == GLFW_PRESS || a == GLFW_REPEAT);
	if (key == GLFW_KEY_DOWN)
		BIT_SET(g_keys, BACK, a == GLFW_PRESS || a == GLFW_REPEAT);
	if (key == GLFW_KEY_D)
		BIT_SET(g_keys, SOBJ_POS_RIGHT, a == GLFW_PRESS || a == GLFW_REPEAT);
	if (key == GLFW_KEY_A)
		BIT_SET(g_keys, SOBJ_POS_LEFT, a == GLFW_PRESS || a == GLFW_REPEAT);
	if (key == GLFW_KEY_W)
		BIT_SET(g_keys, SOBJ_POS_FORWARD, a == GLFW_PRESS || a == GLFW_REPEAT);
	if (key == GLFW_KEY_S)
		BIT_SET(g_keys, SOBJ_POS_BACK, a == GLFW_PRESS || a == GLFW_REPEAT);
	if (key == GLFW_KEY_Q)
		BIT_SET(g_keys, SOBJ_POS_UP, a == GLFW_PRESS || a == GLFW_REPEAT);
	if (key == GLFW_KEY_E)
		BIT_SET(g_keys, SOBJ_POS_DOWN, a == GLFW_PRESS || a == GLFW_REPEAT);
	key_callback3(g_window, key, a, mods);
}
