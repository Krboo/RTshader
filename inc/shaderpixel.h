/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shaderpixel.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalaouf <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 19:37:07 by yalaouf           #+#    #+#             */
/*   Updated: 2017/05/03 22:40:11 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADERPIXEL_H
# define SHADERPIXEL_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# define GL_GLEXT_PROTOTYPES
# define GLFW_INCLUDE_GLCOREARB
# include "GLFW/glfw3.h"
# include "SOIL2.h"
# include "fmod.h"
# include "libft.h"
# undef PLUS

# if __APPLE__
#  define FMOD_LIB "fmod/lib/libfmod.dylib"
# else
#  define FMOD_LIB "fmod/lib/libfmod-linux.so.8.8"
# endif

# define WIN_W 1080
# define WIN_H 720
# define SCALE 70

typedef struct s_scene				t_scene;
typedef struct s_object				t_object;
typedef struct s_image				t_image;
typedef struct s_material			t_material;
typedef struct s_primitive			t_primitive;
typedef struct s_camera				t_camera;

typedef	struct			s_vec2
{
	float				x;
	float				y;
}						t_vec2;

typedef	struct			s_vec3
{
	float				x;
	float				y;
	float				z;
}						t_vec3;

typedef	struct			s_vec4
{
	float				x;
	float				y;
	float				z;
	float				w;
}						t_vec4;

typedef struct			s_file
{
	char				path[1024];
	int					fd;
}						t_file;

typedef struct			s_line_list
{
	char				*line;
	struct s_line_list	*next;
}						t_line_list;

typedef struct			s_shader_file
{
	t_line_list			*true_begin;
	t_line_list			*begin;
	t_line_list			*function_begin;
	t_line_list			*uniform_begin;
	t_line_list			*main_image_begin;
	t_line_list			*raytrace_lights;
	t_line_list			*scene_begin;
	t_line_list			*scene_end;
	t_line_list			*post_processing;
}						t_shader_file;

typedef struct			s_atlas
{
	unsigned char		*data;
	GLuint				id;
	int					width;
	int					height;
}						t_atlas;

enum					e_key_bits
{
	RIGHT,
	LEFT,
	UP,
	DOWN,
	FORWARD,
	BACK,
	PLUS,
	MOIN,
	SOBJ_DIR_X,
	SOBJ_DIR_Y,
	SOBJ_DIR_Z,
	SOBJ_POS_RIGHT,
	SOBJ_POS_FORWARD,
	SOBJ_POS_BACK,
	SOBJ_POS_LEFT,
	SOBJ_POS_UP,
	SOBJ_POS_DOWN,
};

enum					e_sound_format
{
	WAVE,
};

typedef struct			s_sound
{
	int					id;
	int					fd;
	int					tex_length;
	GLint				gl_id;
	char				*image_buffer;
	FMOD_SOUND			*sound;
	enum e_sound_format	sound_format;
}						t_sound;

typedef struct			s_selected
{
	int					pos_uniform;
	int					dir_uniform;
	t_vec3				*dir;
	t_vec3				*pos;
}						t_selected;

# define BIT_SET(i, pos, v) (v) ? (i |= 1 << pos) : (i &= ~(1 << pos))
# define BIT_GET(i, pos) (i >> pos) & 1
# define G_MOVE_AMOUNT 0.05f;

# define VEC3_ADD_DIV(v1, v2, f) {v1.x+=v2.x/(f);v1.y+=v2.y/(f);v1.z+=v2.z/(f);}
# define VEC3_UP ((t_vec3){0, 1, 0})
# define VEC3(v) (t_vec3){v.x, v.y, v.z}
# define VEC3_MULT(v1, v2) (t_vec3){v1.x * v2, v1.y * v2, v1.z * v2}
# define LOL1(x) ft_strrchr(x, '.') != NULL
# define FILE_CHECK_EXT(x, y) (LOL1(x) && !ft_strcmp(ft_strrchr(x, '.') + 1, y))

extern t_vec4			g_mouse;
extern t_vec4			g_move;
extern t_vec2			g_window;
extern t_vec3			g_forward;
extern int				g_shadow;
extern int				g_keys;
extern int				g_input_pause;
extern float			g_paused_time;
extern long				g_last_modified_file[0xF00];
extern float			g_fov;
extern float			g_ambient;
extern t_selected		g_selected_object;
extern int				g_selected_object_index;

GLFWwindow				*init(char *fname);
GLuint					create_program(char *file, bool fatal);
float					get_current_time(void);
bool					file_is_regular(int fd) __attribute__((overloadable));
bool					file_is_regular(char *fd) __attribute__((overloadable));
char					*build_shader(t_scene *scene, char *scene_directory,
										int *atlas_id, t_file *sources);
t_scene					*get_scene(t_scene *scene);
void					save_object_transform(void);
void					select_object(void);

GLuint					create_vbo(void);
GLuint					create_vao(GLuint vbo, int program);
void					check_file_changed(GLuint *program, t_file *files,
											size_t num);
void					recompile_program(t_file *files, GLuint *program);
void					init_source_file(t_file *files, size_t max,
										size_t *num);

t_vec3					vec3_cross(t_vec3 v1, t_vec3 v2);
t_vec3					scale(t_vec3 vect, float f);
t_vec3					mat_rotate(t_vec3 point, t_vec3 rot);
t_vec3					normalize(t_vec3 v);

int						heck_file_extension(char *file, char **exts);
void					display_window_fps(GLFWwindow *win);
char					*get_scene_directory(char *scene_dir);
int						get_program(int p);
GLint					*get_uniform_location(GLuint program);
t_scene					*get_scene(t_scene *scene);
t_vec3					get_object_position(t_object *obj);

void					update_uniforms(GLint *unis, GLint *images);
void					update_keys(void);
void					update_object_transform(void);

unsigned int			texture_repeat(t_image *tex, int x, int y);
unsigned int			apply_channel_mask_pixel(unsigned int pixel, int chans);
unsigned int			channeltomask(int chan);

# define FTN3 int src_mask, int *new_tex_width, int

void					fusion_texture(t_image *dst, t_image *src,
						int dst_mask, FTN3 *new_tex_height);

# define FTN4 int x, int y, t_image *src, t_image

unsigned int			fusion_pixel(int src_mask, int dst_mask, FTN4 *dst);

unsigned int			build_atlas(t_object *obj, int atlas_w,
										int atlas_h, bool first);
GLuint					new_opengl_texture(int width, int height,
											unsigned char *data);
void					load_atlas(t_object *obj, char *scene_directory,
									int *atlas_width, int *atlas_height);
void					add_object_textures_to_atlas(t_material *mat,
												t_atlas *atlas,
												int *offset_x, int *offset_y);
void					add_subimage(t_atlas *atlas, int off_x, int off_y,
									t_image *img);

void					append_uniforms(t_shader_file *shader_file,
										t_object *obj);
char					*generate_coupes_line(t_primitive *prim);
char					*generate_scene_line(t_object *obj);
char					*generate_material_line(t_material *mat);
unsigned char			*generate_image_from_data(float data, \
						int *width, int *height) __attribute__((overloadable));
unsigned char			*generate_image_from_data(t_vec3 data, \
						int *width, int *height) __attribute__((overloadable));
unsigned char			*load_image(char *path, int *width, int *height, \
									int *channels);
char					*build_path(char *dir, char *file);

void					append_post_processing(t_shader_file *shader_file,
												t_camera *c);
void					load_textures_if_exists(t_material *m,
										char *scene_directory,
										int *atlas_width, int *atlas_height);

void					error_callback(int error, const char *description);
void					key_callback3(GLFWwindow *g_window, int key, int a,
										int mods);
void					key_callback2(GLFWwindow *g_window, int key, int a,
										int mods);

static const char		*g_vertex_shader_text =
"#version 330\n"
"in vec2		fragPosition;\n"
"out vec4		outColor;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(fragPosition, 0.0, 1.0);\n"
"}\n";

static const char		*g_fragment_shader_image_text =
"void mainImage(vec2 fragCoord)\n"
"{\n"
"	vec2 uv = fragCoord.xy / iResolution.xy;\n"
"	fragColor = vec4(uv, 0.5 + 0.5 * sin(iGlobalTime), 1.0);\n"
"}\n";

static const char		*g_fragment_shader_text =
"#version 330\n"
"in vec4 outColor;\n"
"out vec4 fragColor;\n"
"\n"
"uniform vec2		iResolution;\n"
"uniform float		iGlobalTime;\n"
"uniform int		iFrame;\n"
"uniform vec4		iMouse;\n"
"uniform vec3		iForward;\n"
"uniform vec4		iMoveAmount;\n"
"uniform sampler2D	atlas;\n"
"uniform float		iFov;"
"uniform float		iAmbient;"
"uniform int		iShadow = 0;\n"
"\n"
"void mainImage(vec2 f);\n"
"\n"
"vec4 texture2D(sampler2D s, vec2 coord, float f)\n"
"{\n"
"	return texture(s, coord, f);\n"
"}\n"
"\n"
"vec4 texture2D(sampler2D s, vec2 coord)\n"
"{\n"
"	return texture(s, coord);\n"
"}\n"
"\n"
"void main()\n"
"{\n"
"	mainImage(gl_FragCoord.xy);\n"
"}\n";

static const char		*g_main_image_start_text =
"#line 1\n"
"float pi = 3.1415;\n"
"void		progressbar(vec2 fragCoord)\n"
"{\n"
"	float radius = 0.3;\n"
"float lineWidth = 5.0; // in pixels\n"
"float glowSize = 5.0; // in pixels\n"
"\n"
"float pixelSize = 1.0 / min(iResolution.x, iResolution.y);\n"
"lineWidth *= pixelSize;\n"
"glowSize *= pixelSize;\n"
"glowSize *= 2.0;\n"
"\n"
"vec2 uv = (fragCoord.xy / iResolution.xy)-0.5;\n"
"uv.x *= iResolution.x/iResolution.y;\n"
"\n"
"float len = length(uv);\n"
"float angle = atan(uv.y, uv.x);\n"
"\n"
"float fallOff = fract(-0.5*(angle/pi)-iGlobalTime*0.5);\n"
"\n"
"lineWidth = (lineWidth-pixelSize)*0.5*fallOff;\n"
"float color = smoothstep(pixelSize, 0.0, abs(radius-len)-lineWidth)*fallOff;\n"
"color += smoothstep(glowSize*fallOff, 0.0, abs(radius - len) - lineWidth)"
"* fallOff *0.5;\n"
"\n"
"fragColor = vec4(color);\n"
"}\n"
"\n"
"void        mainImage(vec2 coord)\n"
"{\n"
"	vec2    uv = ((coord / iResolution) - .5) * 2.f;\n"
"	vec3    cameraPos = iMoveAmount.xyz;\n"
"	vec3    cameraDir = iForward;\n"
"	vec3    col;\n"
"\n"
"	//window ratio correciton:\n"
"	uv.x *= iResolution.x / iResolution.y;\n"
"	if (iGlobalTime < 3.f) { progressbar(coord); return ;}\n"
"\n"
"	//perspective view\n"
"	vec3    forw = normalize(iForward);\n"
"	vec3    right = normalize(cross(forw, vec3(0, 1, 0)));\n"
"	vec3    up = normalize(cross(right, forw));\n"
"	vec3    rd = normalize(uv.x * right + uv.y * up + iFov * forw);\n"
"	fragColor = vec4(raytrace(cameraPos, rd), 0);\n"
"}\n";

static const char		*g_scene_start_text =
"Hit     scene(Ray r)\n"
"{\n"
"	int i = -1;\n"
"Hit hit = Hit(1e20,vec3(0,0,0),vec3(0,0,0),Material(vec4(0,0,0,0),"
"vec4(0,0,0,0),vec4(0,0,0,0),vec4(0,0,0,0),vec4(0,0,0,0),vec4(0,0,0,0)"
", 0, 0),vec2(0,0),false, 0, 0);\n";

static const char		*g_scene_end_text =
"    return hit;\n"
"}\n";

static const char		*g_shader_header_text =
"struct      Ray\n"
"{\n"
"    vec3    dir;\n"
"    vec3    pos;\n"
"};\n"
"\n"
"struct  Coupes\n"
"{\n"
"    vec4		 t[5];\n"
"		 int		 nsl;\n"
"};\n"
"\n"
"struct  Material\n"
"{\n"
"	vec4		texture;\n"
"	vec4		emission;\n"
"	vec4		specular;\n"
"	vec4		reflection;\n"
"	vec4		refraction;\n"
"	vec4		bump;\n"
"	int			color_effect;\n"
"	int			normal_effect;\n"
"};\n"
"\n"
"struct      Hit\n"
"{\n"
"   float  		dist;\n"
"   vec3    	norm;\n"
"   vec3    	pos;\n"
"	Material	mat;\n"
"	vec2		uv;\n"
"	bool		inside;\n"
"	int			color_effect;\n"
"	int			normal_effect;\n"
"};\n"
"\n"
"Hit       scene(Ray r);\n"
"vec3    raytrace(vec3 ro, vec3 rd);\n";

static const char		*g_raytrace_start_text =
"vec3    raytrace(vec3 ro, vec3 rd)\n"
"{\n"
"   Ray         r;\n"
"   Hit         h;\n"
"   vec3        color = vec3(0,0,0);\n"
"   vec3        ambient;\n"
"   r.dir = rd;\n"
"	r.pos = ro;\n";

static const char		*g_raytrace_end_text =
"	return (color);\n"
"}\n";

#endif
