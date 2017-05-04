/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_shader_include.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalaouf <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 14:13:23 by pmartine          #+#    #+#             */
/*   Updated: 2017/05/03 22:01:33 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILD_SHADER_INCLUDE_H
# define BUILD_SHADER_INCLUDE_H

# define MAX_TEXTURES	512
# define N_L_L2 m->next = NULL; m->line = NULL; m;})
# define N_L_L (sizeof(t_line_list)))) ft_exit("malloc error !"); N_L_L2
# define NEW_LINE_LIST ({t_line_list *m; if (!(m = (t_line_list *)malloc N_L_L
# define YO(l) tmp->next = l->next; l->next = tmp;}
# define LIST_INSERT(l,s) {t_line_list *tmp=NEW_LINE_LIST; tmp->line = s;YO(l)
# define Y2(l) tmp->next = l->next; l->next = tmp; l = tmp;}
# define LIST_APPEND(l, s) {t_line_list *tmp = NEW_LINE_LIST; tmp->line=s;Y2(l)
# define ISTYPE(x) (obj->primitive.type == x + 1)
# define PRM2 ISTYPE(GLASS) || ISTYPE(DISK))
# define PRM ISTYPE(CONE) || ISTYPE(CUBE) || ISTYPE(CUBE_TROUE) || PRM2
# define ISPRIMITIVE (ISTYPE(SPHERE) || ISTYPE(PLANE) || ISTYPE(CYLINDRE) ||PRM
# define TPE ISTYPE(SPOT_LIGHT))
# define ISLIGHT (ISTYPE(POINT_LIGHT) || ISTYPE(DIRECTIONAL_LIGHT) || TPE
# define MAX(x, y) ((x > y) ? x : y)
# define MAX_SHADER_FILE_SIZE	0xF000
# define LAST(img) img.atlas_uv.w
# define GET_UVS(img) img.atlas_uv.x, img.atlas_uv.y, img.atlas_uv.z, LAST(img)
# define GET_VEC4(vec) vec.x, vec.y, vec.z, vec.w
# define LDTX5(m,p,o) generate_image_from_data(m->o, &m->p.width, &m->p.height);
# define LDTX4(m,p,o) &m->p.channels); else m->p.data = LDTX5(m, p, o)
# define LDTX3(m,p,o) m->p.file), &m->p.width, &m->p.height, LDTX4(m, p, o)
# define LDTX2(m,p,o) load_image(build_path(scene_directory, LDTX3(m, p, o)
# define LDTX(m,p,o) (m->has_##p && m->p.file[0]) m->p.data = LDTX2(m, p, o)
# define LOAD_TEXTURE(m, p, o) if LDTX(m, p, o)
# define LOAD_TEXTURE_ATLAS(m,p,o,aw,ah) LOAD_TEXTURE(m, p, o);LTA(m,p,o,aw,ah)
# define LTA(m,p,o,aw,ah) *aw += m->p.width; *ah = MAX(*ah, m->p.height);
# define T3(tex,x,y) * tex->channels + _x * tex->channels)), tex->channels);})
# define T2(tex,x,y) ((*(unsigned int *)(tex->data + _y * tex->width T3(tex,x,y)
# define T1(tex,x,y) _y = y % tex->height; apply_channel_mask_pixel T2(tex,x,y)
# define TEXTURE_REPEAT(tex, x, y) ({int _x = x % tex->width; int T1(tex,x,y)
# define MIN(x, y) ((x) < (y)) ? (x) : (y)
# define OCTET(x, c) (((x) >> c) & 0xFF)
# define FU2(p1,m1,p2,m2,c) (((OCTET(p2 & m2, c))*(OCTET(p1 & m1, c)) / 255)<<c)
# define FU(p1,m1,p2,m2,c) == 0x00) ? OCTET(p1, c) << c : FU2(p1,m1,p2,m2,c)
# define FUSION_PIXEL_COMPONENT(p1,m1,p2,m2,c) (OCTET(m2, c) FU(p1,m1,p2,m2,c)
# define FA6(m,p1,p2,aw,ah,m1,m2) m->p1.width; *ah = MAX(*ah, m->p1.height); }
# define FA5(m,p1,p2,aw,ah,m1,m2) &new_y); *aw += FA6(m,p1,p2,aw,ah,m1,m2)
# define FA4(m,p1,p2,aw,ah,m1,m2) &m->p2,m1,m2,&new_x, FA5(m,p1,p2,aw,ah,m1,m2)
# define FA3(m,p1,p2,aw,ah,m1,m2) fusion_texture(&m->p1,FA4(m,p1,p2,aw,ah,m1,m2)
# define FA2(m,p1,p2,aw,ah,m1,m2) *aw -= m->p1.width; FA3(m,p1,p2,aw,ah,m1,m2)
# define FA(m,p1,p2,aw,ah,m1,m2) { int new_x, new_y; FA2(m,p1,p2,aw,ah,m1,m2)
# define FUSION_TEXTURE_ATLAS(m,p1,p2,aw,ah,m1,m2) FA(m,p1,p2,aw,ah,m1,m2)
# define W			0xFF000000
# define XYZ		0xFFFFFFFF
# define COF4(m,p) m->p.height) / (float)atlas->height}
# define COF3(m,p) / (float)atlas->width, (float)(*offset_y + COF4(m,p)
# define COF2(m,p) (float)atlas->height, (float)(*offset_x +m->p.width)COF3(m,p)
# define COF(m,p) (float)atlas->width, (float)*offset_y / COF2(m,p)
# define COMPUTE_OFFSET(m, p) (t_vec4){(float)*offset_x / COF(m,p)
# define ADD_TEXTURE_ATLAS(m, p) add_subimage(atlas, ATA(m,p)
# define ATA(m,p) *offset_x, *offset_y, &m->p); m->p.atlas_uv = ATA2(m,p)
# define ATA2(m,p) COMPUTE_OFFSET(m, p); *offset_x += m->p.width;
# define SHA6 "shaders/pproc.glsl", NULL
# define SHA5 "shaders/cube.glsl", "shaders/light.glsl", SHA6
# define SHA4 "shaders/disk.glsl", "shaders/tore_de_sphere.glsl", SHA5
# define SHA3 "shaders/cubetroue.glsl", "shaders/glass.glsl", SHA4
# define SHA2 "shaders/cone.glsl", "shaders/plane.glsl", SHA3
# define SHA "shaders/sphere.glsl", "shaders/cylinder.glsl", SHA2
# define SHADERS "shaders/scene.glsl", "shaders/noise.glsl", SHA

#endif
