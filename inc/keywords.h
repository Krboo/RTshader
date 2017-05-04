/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keywords.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 00:14:55 by alelievr          #+#    #+#             */
/*   Updated: 2017/05/03 20:07:48 by yalaouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYWORDS_H
# define KEYWORDS_H

typedef struct	s_keypair
{
	char		*name;
	int			value;
}				t_keypair;

const char		*g_restricted_keywords[] = {
	"type:", "pos:", "rot:", "color:", "csg:", "radius:", "scale:", "slice:",
	"mesh:", "filter:", "texture:", "emission color:",
	"highlight color:", "opacity:", "reflection:", "refraction:",
	"bumpmap:", "illum:", "emission color map:", "highlight color map:",
	"refraction map:", "reflection map:", "ambiant color:", "rotate:",
	"moving:", "effect:", "color_effect:", "normal_effect:", NULL
};

# define END -1
# define V(x) {#x, x}

const struct	s_kek
{
	char		*name;
	int			value;
}

illum_restricted_keywords[] = {
	V(AMBIANT), V(CAST_SHADOW), V(RECEIVE_SHADOW), V(REFLECT), V(END)
};

const t_keypair	g_mask_restricted_keywords[] = {
	V(SEPIA), V(CARTOON), V(BLACK_AND_WHITE), V(DEPTH_OF_FIELD),
	V(ACES_TONEMAPPING), V(VIGNETTING), V(DALTONIZE),
	V(NIGHT_VISION), V(END)
};

const t_keypair g_illum_restricted_keywords[] = {
	V(AMBIANT), V(CAST_SHADOW), V(RECEIVE_SHADOW), V(REFLECT), V(END)
};

const t_keypair	g_color_effect_r_k[] = {
	V(CHECKERBOARD),
	V(BRICK),
	V(NOISE),
	V(MOVING_NOISE),
	V(FBM),
	V(END)
};

const t_keypair	g_normal_effect_r_k[] = {
	V(N_NOISE),
	V(N_MOVING_NOISE),
	V(N_FBM),
	V(END)
};

const char		*g_type_restricted_keywords[] = {
	"SPHERE", "PLANE", "CYLINDRE", "CONE", "CUBE", "GLASS", "DISK",
	"CUBE_TROUE", "TORE_DE_SPHERE", "CAMERA", "POINT_LIGHT", "SPOT_LIGHT",
	"DIRECTIONAL_LIGHT", NULL
};

#endif
