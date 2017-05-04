/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_shader_lines.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 14:28:45 by pmartine          #+#    #+#             */
/*   Updated: 2017/05/02 19:48:14 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "build_shader_include.h"
#include "shaderpixel.h"

static void		append_camera_uniforms(t_object *obj)
{
	g_move.x = obj->transform.position.x;
	g_move.y = obj->transform.position.y;
	g_move.z = obj->transform.position.z;
	if (obj->camera.fov > 0)
		g_fov = obj->camera.fov;
	if (obj->camera.ambient > 0)
		g_ambient = obj->camera.ambient;
}

void			append_uniforms(t_shader_file *shader_file, t_object *obj)
{
	static char		line[0xF000];

	if (!ISTYPE(CAMERA))
	{
		sprintf(line, "uniform vec3 %s_position = vec3(%f, %f, %f);",\
			obj->name, obj->transform.position.x, obj->transform.position.y, \
obj->transform.position.z);
		LIST_APPEND(shader_file->uniform_begin, strdup(line));
		sprintf(line, "uniform vec3 %s_rotation = vec3(%f, %f, %f);",\
			obj->name, obj->transform.euler_angles.x, \
obj->transform.euler_angles.y, obj->transform.euler_angles.z);
		LIST_APPEND(shader_file->uniform_begin, strdup(line));
	}
	if (ISLIGHT)
	{
		sprintf(line, "\tcolor += calc_color(r, %s_position, vec3(%f, %f, %f), \
%f);",\
			obj->name, obj->light_prop.color.x, obj->light_prop.color.y, \
obj->light_prop.color.z, obj->light_prop.intensity);
		LIST_APPEND(shader_file->raytrace_lights, strdup(line));
	}
	else if (ISTYPE(CAMERA))
		append_camera_uniforms(obj);
}

char			*generate_coupes_line(t_primitive *prim)
{
	static char		line[0xF00];

	sprintf(line, "vec4[5](vec4(%f, %f, %f, %f), vec4(%f, %f, %f, %f),\
		vec4(%f, %f, %f, %f), vec4(%f, %f, %f, %f), vec4(%f, %f, %f, %f)), %d",
		GET_VEC4(prim->slice[0]),
		GET_VEC4(prim->slice[1]),
		GET_VEC4(prim->slice[2]),
		GET_VEC4(prim->slice[3]),
		GET_VEC4(prim->slice[4]),
		prim->nsl);
	return (line);
}

static char		*generate_scene_line2(char *line, t_object *obj)
{
	if (ISTYPE(CUBE))
		sprintf(line, "\tcube(%s_position, %s_rotation, %f, Material(%s), r, \
hit);", obj->name, obj->name, obj->primitive.height, \
generate_material_line(&obj->material));
	else if (ISTYPE(GLASS))
		sprintf(line, "\tglass(%s_position, %s_rotation, %f, Material(%s), r, \
hit);", obj->name, obj->name, obj->primitive.height, \
generate_material_line(&obj->material));
	else if (ISTYPE(DISK))
		sprintf(line, "\tdisk(%s_rotation, %s_position, %f, Material(%s), r, \
hit);", obj->name, obj->name, obj->primitive.height, \
generate_material_line(&obj->material));
	else if (ISTYPE(TORE_DE_SPHERE))
		sprintf(line, "\ttore_de_sphere(%s_position , %s_rotation, %f, \
Material(%s), r, hit);", obj->name, obj->name, obj->primitive.height, \
generate_material_line(&obj->material));
	else
		return (NULL);
	return (strdup(line));
}

char			*generate_scene_line(t_object *obj)
{
	static char		line[0xF00];

	if (ISTYPE(SPHERE))
		sprintf(line, "\tsphere(%s_position, %s_rotation, %f, Coupes(%s), \
Material(%s), r, hit);", obj->name, obj->name, obj->primitive.radius, \
generate_coupes_line(&obj->primitive), generate_material_line(&obj->material));
	else if (ISTYPE(PLANE))
		sprintf(line, "\tplane(%s_rotation, %s_position, 0, Coupes(%s), \
Material(%s), r, hit);", obj->name, obj->name, \
generate_coupes_line(&obj->primitive), generate_material_line(&obj->material));
	else if (ISTYPE(CYLINDRE))
		sprintf(line, "\tcyl(%s_position, %s_rotation, %f, Coupes(%s), \
Material(%s), r, hit);", obj->name, obj->name, obj->primitive.angle, \
generate_coupes_line(&obj->primitive), generate_material_line(&obj->material));
	else if (ISTYPE(CONE))
		sprintf(line, "\tcone(%s_position, %s_rotation, %f, Coupes(%s), \
Material(%s), r, hit);", obj->name, obj->name, obj->primitive.angle, \
generate_coupes_line(&obj->primitive), generate_material_line(&obj->material));
	else if (ISTYPE(CUBE_TROUE))
		sprintf(line, "\tcubetroue(%s_position, %s_rotation, %f, Material(%s), \
r, hit);", obj->name, obj->name, obj->primitive.height, \
generate_material_line(&obj->material));
	else
		return (generate_scene_line2(line, obj));
	return (strdup(line));
}
