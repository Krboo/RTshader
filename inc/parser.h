/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/08 14:47:27 by alelievr          #+#    #+#             */
/*   Updated: 2017/05/03 20:09:42 by yalaouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "shaderpixel.h"
# include "libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <stdarg.h>
# include <stdbool.h>

# define POS		"\\spos:\\s%f\\s%f\\s%f\\s"
# define ROT		"\\srot:\\s%f\\s%f\\s%f\\s"

# define COLOR_F	"\\scolor:\\s%f\\s%f\\s%f\\s"
# define COLOR_V	"\\scolor:\\s%z\\s"
# define EMISSION_COLOR_F "\\semission color:\\s%f\\s%f\\s%f\\s"
# define EMISSION_COLOR_V "\\semission color:\\s%z\\s"
# define HIGHLIGHT_COLOR_F "\\shighlight color:\\s%f\\s%f\\s%f\\s"
# define HIGHLIGHT_COLOR_V "\\shighlight color:\\s%z\\s"

# define OPACITY "\\sopacity:\\s%f\\s"
# define SPECULAR "\\sspecular:\\s%f\\s"
# define REFL "\\sreflection:\\s%f\\s"
# define REFR "\\srefraction:\\s%f\\s"
# define INTENSITY "\\sintensity:\\s%f\\s"
# define ANGLE "\\sangle:\\s%f\\s"
# define RADIUS "\\sradius:\\s%f\\s"
# define HEIGHT "\\sheight:\\s%f\\s"

# define FOV "\\sfov:\\s%f\\s"
# define AMBIENT "\\sambient:\\s%f\\s"

# define SLICE "\\sslice:\\s%f\\s%f\\s%f\\s%f\\s"

# define TEXTURE	"\\stexture:\\s%s\\s"
# define BUMPMAP	"\\sbumpmap:\\s%s\\s"
# define EMISSION_MAP	"\\semission color map:\\s%s\\s"
# define HIGH_MAP "\\shighlight color map:\\s%s\\s"
# define REFR_MAP	"\\srefraction map:\\s%s\\s"
# define OPACITY_MAP "\\sopacity map:\\s%s\\s"
# define SPECULAR_MAP "\\sspecular map:\\s%s\\s"
# define REFL_MAP "\\sreflection map map:\\s%s\\s"

# define NAME "\\sname:\\s%s\\s"
# define MASK "\\seffect:\\s%s\\s"
# define ILLUM "\\sillum:\\s%s\\s"
# define TYPE "\\stype:\\s%s\\s"

# define MOVE		"\\smoving:\\s%w\\s%f\\s%f\\s"
# define ROTATE	"\\srotate:\\s%w\\s%f\\s%f\\s"

# define COLOR_EFFECT		"\\scolor_effect:\\s%w\\s"
# define NORMAL_EFFECT	"\\snormal_effect:\\s%w\\s"

# define MTL			"\\smtl:\\sfiles/%w\\s"
# define AMBIANCE	"\\sambiance:\\s%w\\s%f\\s"
# define GATE_XOR "\\scsg:\\s%w\\s"
# define GATE_OR
# define GATE_AND
# define GATE_NAND

# define LOL1(x) ft_strrchr(x, '.') != NULL
# define FILE_CHECK_EXT(x, y) (LOL1(x) && !ft_strcmp(ft_strrchr(x, '.') + 1, y))
# define FTRGB float *r, float *g, float

# define NO4(var, n)((*s)->root_view, n)) ft_exit("name already exist: %s\n",n);
# define NO3(var, n)if (c != NULL && name_already_exists NO4(var, n)
# define NO2(var, n)strcpy(var->name, format_name(n)); NO3(var, n)
# define NO1(var, n)sizeof(t_object)); init_default_object(var); NO2(var, n)
# define NO(var, n)if (!var) ft_exit("malloc error"); bzero(var, NO1(var, n)
# define NEW_OBJECT(var, n) var = (t_object *)malloc(sizeof(t_object));NO(var,n)
# define SS(t) while(*t&&ft_isspace(*t))t++;
# define SKIP_EMPTY_LINE(l) {char*t=l;SS(t);if (*t==0)continue;}
# define FP4(X, line) fill_prop_vec4) (X, line)
# define FP3(X, line)t_primitive *:fill_prop_primitive, t_vec4 *: FP4(X,line)
# define FP2(X, line)fill_prop_material, t_camera *:fill_prop_camera,FP3(X,line)
# define FP1(X, line)t_transform *: fill_prop_transform, t_material*:FP2(X,line)
# define FILL_PROP(X, line) _Generic((X), t_light *: fill_prop_light,FP1(X,line)
# define A(c, line, p1) FILL_PROP(&c-> p1, line);

enum					e_primitive_type
{
	SPHERE,
	PLANE,
	CYLINDRE,
	CONE,
	CUBE,
	GLASS,
	DISK,
	CUBE_TROUE,
	TORE_DE_SPHERE,
	CAMERA,
	POINT_LIGHT,
	SPOT_LIGHT,
	DIRECTIONAL_LIGHT,
};

enum					e_post_processing
{
	SEPIA = 0x0001,
	BLACK_AND_WHITE = 0x0002,
	CARTOON = 0x0004,
	ANTIALIASING = 0x0008,
	DEPTH_OF_FIELD = 0x0010,
	ACES_TONEMAPPING = 0x0080,
	VIGNETTING = 0x0100,
	DALTONIZE = 0x0200,
	NIGHT_VISION = 0x0400,
};

enum					e_color_effect
{
	CHECKERBOARD,
	BRICK,
	NOISE,
	MOVING_NOISE,
	FBM
};

enum					e_normal_effect
{
	N_NOISE,
	N_MOVING_NOISE,
	N_FBM,
};

enum					e_illumination
{
	AMBIANT = 0x001,
	CAST_SHADOW = 0x002,
	RECEIVE_SHADOW = 0x004,
	REFLECT = 0x008,
};

typedef	struct			s_map
{
	char				*fmt;
	struct s_image		*img;
	bool				*active;
}						t_map;

# define DATA union { float radius; float height; float angle; };int

typedef	struct			s_primitive
{
	int					type;
	DATA				kek;
	t_vec4				slice[5];
	int					nsl;
}						t_primitive;

typedef struct			s_transform
{
	t_vec3				position;
	t_vec3				initial_position;
	t_vec3				euler_angles;
	t_vec3				normal;
}						t_transform;

typedef struct			s_image
{
	char				file[1024];
	unsigned char		*data;
	int					width;
	int					height;
	int					channels;
	t_vec4				atlas_uv;
}						t_image;

typedef	struct			s_material
{
	char				name[256];
	int					illum;
	t_vec3				color;
	t_vec3				emission_color;
	t_vec3				highlight_color;
	float				opacity;
	float				specular;
	float				reflection;
	float				refraction;
	float				bump;
	t_image				texture;
	t_image				bumpmap;
	t_image				emission_map;
	t_image				highlight_map;
	t_image				reflection_map;
	t_image				refraction_map;
	t_image				opacity_map;
	t_image				specular_map;
	bool				has_texture;
	bool				has_bumpmap;
	bool				has_emission_map;
	bool				has_highlight_map;
	bool				has_reflection_map;
	bool				has_refraction_map;
	bool				has_opacity_map;
	bool				has_specular_map;
	int					color_effect;
	int					normal_effect;
}						t_material;

# define NB	union { int nb_vertex; int nb_normals; int nb_uvs; };int

typedef struct			s_submesh
{
	char				name[128];
	t_material			*material;
	t_vec3				*vertex;
	t_vec3				*normals;
	t_vec2				*uvs;
	int					*triangles;
	NB					nb_data;
	int					nb_triangles;
}						t_submesh;

typedef	struct			s_mesh
{
	t_submesh			*submeshs;
	int					nb_submesh;
	t_vec3				scale;
}						t_mesh;

typedef struct			s_camera
{
	float				fov;
	float				ambient;
	int					post_processing_mask;
}						t_camera;

typedef struct			s_light
{
	t_vec3				color;
	float				intensity;
}						t_light;

typedef struct			s_object
{
	char				name[256];
	int					indent_level;
	t_transform			transform;
	t_light				light_prop;
	t_mesh				mesh;
	t_primitive			primitive;
	t_material			material;
	t_camera			camera;
	bool				is_primitive;
	t_vec4				move;
	t_vec4				rotate;
	float				laps;
	struct s_object		*children;
	struct s_object		*parent;
	struct s_object		*brother_of_children;
}						t_object;

typedef struct			s_scene
{
	int					nb_object;
	t_object			*root_view;
}						t_scene;

void					parse_obj(char *file, t_mesh **mesh);
void					parse_mtl(t_mesh *mesh);
int						gl(char *dst, int *fd);
void					parse_obj_file(char *file, t_mesh *mesh);
int						get_next_word(char **str, char *res);
int						parse(int ac, char **av);
void					fill_prop_vec4(t_vec4 *data, char *line);
void					fill_prop_camera(t_camera *cam, char *line);
void					fill_prop_primitive(t_primitive *p, char *line);
void					fill_prop_light(t_light *l, char *line);
void					fill_prop_transform(t_transform *t, char *line);
void					fill_prop_map(t_material *m, char *line,
										char *word, char *str);
void					fill_prop_material(t_material *mtl, char *line);
void					fill_prop_material_effect(t_material *mtl, char *line);
void					init_default_object(t_object *o);
bool					check_obj_line(char *line, char *obj_name,
										int *indent_level);
char					*format_name(char *name);
void					display_objects(t_object *lst_obj);
bool					name_already_exists(t_object *obj, char *name);
bool					obj_file(char *obj_name, char *k);
char					*format_name(char *name);
void					display_objects(t_object *lst_obj);
bool					name_already_exists(t_object *obj, char *name);
void					parse_rt_file(char *file, t_scene *prim);
void					skip_space(char **format, char **str);
int						skip_string(char **format, char **str);
int						convert_float(char **format, char **str, float *f);
int						convert_int(char **format, char **str, int *i);
int						convert_word(char **format, char **str,
									char *ptr, int buffsize);
int						convert_str(char **format, char **str,
									char *ptr, int buffsize);
void					rgbcolor(int color, float *r, float *g, float *b);
int						hexa(char *str);
int						convert_color(char **format, char **str, FTRGB *b);
int						sscanf_return(int value, va_list *vargs);
int						ft_sscanf(char *format, char *str, ...);

#endif
