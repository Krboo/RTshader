/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shaderutils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 10:58:21 by alelievr          #+#    #+#             */
/*   Updated: 2017/05/02 18:11:35 by pmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shaderpixel.h"
#include "parser.h"

GLint			*get_uniform_location(GLuint program)
{
	static GLint unis[0xF0];

	unis[0] = glGetUniformLocation(program, "iGlobalTime");
	unis[1] = glGetUniformLocation(program, "iFrame");
	unis[2] = glGetUniformLocation(program, "iMouse");
	unis[3] = glGetUniformLocation(program, "iForward");
	unis[4] = glGetUniformLocation(program, "iMoveAmount");
	unis[5] = glGetUniformLocation(program, "iResolution");
	unis[6] = glGetUniformLocation(program, "iFov");
	unis[7] = glGetUniformLocation(program, "iAmbient");
	unis[8] = glGetUniformLocation(program, "iShadow");
	unis[9] = 9;
	return (unis);
}

t_scene			*get_scene(t_scene *scene)
{
	static t_scene	*scn = NULL;

	if (scene != NULL)
		scn = scene;
	return (scn);
}

t_vec3			get_object_position(t_object *obj)
{
	const t_vec3	mask_x = normalize((t_vec3){0, 1, 1});
	const t_vec3	mask_y = normalize((t_vec3){1, 0, 1});
	const t_vec3	mask_z = normalize((t_vec3){1, 1, 0});
	t_vec3			pos;
	t_vec3			rotate;

	pos = (t_vec3){0, 0, 0};
	if (obj->move.x == 0 && obj->move.y == 0 && obj->move.z == 0)
		return (obj->transform.initial_position);
	pos.x = obj->transform.initial_position.x + mask_x.x * obj->move.x
		+ mask_y.x * obj->move.y + mask_z.x * obj->move.z;
	pos.y = obj->transform.initial_position.y + mask_x.y * obj->move.x
		+ mask_y.y * obj->move.y + mask_z.y * obj->move.z;
	pos.z = obj->transform.initial_position.z + mask_x.z * obj->move.x
		+ mask_y.z * obj->move.y + mask_z.z * obj->move.z;
	rotate = mat_rotate(pos, VEC3_MULT(normalize(VEC3(obj->move)), obj->laps));
	obj->laps += obj->move.w;
	VEC3_ADD_DIV(rotate, obj->transform.initial_position, 1);
	return (rotate);
}
