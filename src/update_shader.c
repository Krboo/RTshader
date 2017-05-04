/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_shader.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 10:51:06 by alelievr          #+#    #+#             */
/*   Updated: 2017/05/02 21:53:29 by pmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shaderpixel.h"
#include "parser.h"

void			update_uniforms(GLint *unis, GLint *images)
{
	static int		frames = 0;
	const float		ti = get_current_time();

	if (!g_input_pause)
		glUniform1f(unis[0], ti);
	glUniform1i(unis[1], frames++);
	glUniform4f(unis[2], g_mouse.x, WIN_H - g_mouse.y, g_mouse.y, g_mouse.y);
	glUniform3f(unis[3], g_forward.x, g_forward.y, g_forward.z);
	glUniform4f(unis[4], g_move.x, g_move.y, g_move.z, g_move.w);
	glUniform2f(unis[5], g_window.x, g_window.y);
	glUniform1f(unis[6], g_fov);
	glUniform1f(unis[7], g_ambient);
	glUniform1i(unis[8], g_shadow);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, images[0]);
	glUniform1i(unis[9], images[0]);
	if (g_selected_object.pos_uniform != -1)
		glUniform3fv(g_selected_object.pos_uniform, 1,
				&g_selected_object.pos->x);
	if (g_selected_object.dir_uniform != -1)
		glUniform3fv(g_selected_object.dir_uniform, 1,
				&g_selected_object.dir->x);
}

void			update_selected_keys(void)
{
	if (g_selected_object.dir_uniform == -1)
		return ;
	if (BIT_GET(g_keys, SOBJ_POS_RIGHT))
		g_selected_object.pos->x += .3;
	if (BIT_GET(g_keys, SOBJ_POS_LEFT))
		g_selected_object.pos->x -= .3;
	if (BIT_GET(g_keys, SOBJ_POS_FORWARD))
		g_selected_object.pos->z += .3;
	if (BIT_GET(g_keys, SOBJ_POS_BACK))
		g_selected_object.pos->z -= .3;
	if (BIT_GET(g_keys, SOBJ_POS_UP))
		g_selected_object.pos->y += .3;
	if (BIT_GET(g_keys, SOBJ_POS_DOWN))
		g_selected_object.pos->y -= .3;
	if (BIT_GET(g_keys, SOBJ_DIR_X))
		g_selected_object.dir->x += 1;
	if (BIT_GET(g_keys, SOBJ_DIR_Y))
		g_selected_object.dir->y += 1;
	if (BIT_GET(g_keys, SOBJ_DIR_Z))
		g_selected_object.dir->z += 1;
}

void			update_keys(void)
{
	t_vec3	right;
	t_vec3	up;

	right = vec3_cross(g_forward, VEC3_UP);
	up = vec3_cross(g_forward, right);
	if (BIT_GET(g_keys, RIGHT))
		VEC3_ADD_DIV(g_move, right, 10 / g_move.w);
	if (BIT_GET(g_keys, LEFT))
		VEC3_ADD_DIV(g_move, -right, 10 / g_move.w);
	if (BIT_GET(g_keys, UP))
		VEC3_ADD_DIV(g_move, up, 10 / g_move.w);
	if (BIT_GET(g_keys, DOWN))
		VEC3_ADD_DIV(g_move, -up, 10 / g_move.w);
	if (BIT_GET(g_keys, FORWARD))
		VEC3_ADD_DIV(g_move, g_forward, 10 / g_move.w);
	if (BIT_GET(g_keys, BACK))
		VEC3_ADD_DIV(g_move, -g_forward, 10 / g_move.w);
	update_selected_keys();
	if (BIT_GET(g_keys, PLUS))
		g_move.w *= 1 + G_MOVE_AMOUNT;
	if (BIT_GET(g_keys, MOIN))
		g_move.w *= 1 - G_MOVE_AMOUNT;
}

static t_vec3	get_object_rotation(t_object *obj)
{
	t_vec3	*rot;

	rot = &obj->transform.euler_angles;
	if (obj->rotate.x != 0)
		rot->x += obj->rotate.w;
	if (obj->rotate.y != 0)
		rot->y += obj->rotate.w;
	if (obj->rotate.z != 0)
		rot->z += obj->rotate.w;
	return (*rot);
}

void			update_object_transform(void)
{
	const t_scene		*scene = get_scene(NULL);
	t_object			*obj;
	char				buff[0xF00];

	obj = scene->root_view;
	while (obj)
	{
		if (obj->primitive.type == CAMERA + 1)
		{
			obj = obj->brother_of_children;
			continue ;
		}
		obj->transform.position = get_object_position(obj);
		obj->transform.euler_angles = get_object_rotation(obj);
		sprintf(buff, "%s_euler_angles", obj->name);
		glUniform3fv(glGetUniformLocation(get_program(-1), buff), 1,
				&obj->transform.euler_angles.x);
		sprintf(buff, "%s_position", obj->name);
		glUniform3fv(glGetUniformLocation(get_program(-1), buff), 1,
				&obj->transform.position.x);
		obj = obj->brother_of_children;
	}
}
