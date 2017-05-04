/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 10:45:41 by alelievr          #+#    #+#             */
/*   Updated: 2017/05/02 18:21:35 by pmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shaderpixel.h"
#include <math.h>

#define LENGTH(v) (sqrt(v.x * v.x + v.y * v.y + v.z * v.z))

t_vec3			vec3_cross(t_vec3 v1, t_vec3 v2)
{
	return ((t_vec3){
		v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x});
}

t_vec3			scale(t_vec3 vect, float f)
{
	vect.x *= f;
	vect.y *= f;
	vect.z *= f;
	return (vect);
}

t_vec3			mat_rotate(t_vec3 point, t_vec3 rot)
{
	const float	d = M_PI / 180;
	t_vec3		res;

	rot = scale(rot, d);
	INIT(float, sx, sin(rot.x));
	INIT(float, sy, sin(rot.y));
	INIT(float, sz, sin(rot.z));
	INIT(float, cx, cos(rot.x));
	INIT(float, cy, cos(rot.y));
	INIT(float, cz, cos(rot.z));
	IINIT(float, mat[3][3], (float[3][3]){
		{cz * cy, -1 * cy * sz, sy},
		{sz * cx + sy * sx * cz, -1 * sx * sy * sz + cx * cz, -1 * sx * cy},
		{-1 * sy * cz * cx + sx * sz, cx * sy * sz + sx * cz, cx * cy}
	});
	res.x = point.x * mat[0][0] + point.y * mat[0][1] + point.z * mat[0][2];
	res.y = point.x * mat[1][0] + point.y * mat[1][1] + point.z * mat[1][2];
	res.z = point.x * mat[2][0] + point.y * mat[2][1] + point.z * mat[2][2];
	return (res);
}

t_vec3			normalize(t_vec3 v)
{
	const float l = LENGTH(v);

	return ((t_vec3){v.x / l, v.y / l, v.z / l});
}
