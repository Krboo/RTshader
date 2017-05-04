/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 14:14:54 by pmartine          #+#    #+#             */
/*   Updated: 2017/05/03 21:57:06 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "shaderpixel.h"
#include "build_shader_include.h"

unsigned int		channeltomask(int chan)
{
	unsigned int	ret;

	ret = 0;
	if (chan == 0)
		return (-1);
	while (chan--)
		ret |= 255 << ((8 * chan));
	return (ret);
}

unsigned int		apply_channel_mask_pixel(unsigned int pixel, int chans)
{
	pixel &= channeltomask(chans);
	if (chans == 3)
	{
		pixel |= 0xFF000000;
	}
	return (pixel);
}

unsigned int		texture_repeat(t_image *tex, int x, int y)
{
	if (tex->width == 0 || tex->height == 0)
		return (0);
	else
	{
		x = x % tex->width;
		y = y % tex->height;
		return (apply_channel_mask_pixel((*(unsigned int *)(tex->data + \
	y * tex->width * tex->channels + x * tex->channels)), tex->channels));
	}
}

unsigned int		fusion_pixel(int src_mask, int dst_mask, FTN4 *dst)
{
	unsigned int	src_pixel;
	unsigned int	dst_pixel;
	unsigned int	result_pixel;

	src_pixel = texture_repeat(src, x, y);
	dst_pixel = texture_repeat(dst, x, y);
	result_pixel = 0;
	result_pixel |= FUSION_PIXEL_COMPONENT(dst_pixel, dst_mask, \
	src_pixel, src_mask, 0);
	result_pixel |= FUSION_PIXEL_COMPONENT(dst_pixel, dst_mask, \
	src_pixel, src_mask, 8);
	result_pixel |= FUSION_PIXEL_COMPONENT(dst_pixel, dst_mask, \
	src_pixel, src_mask, 16);
	result_pixel |= FUSION_PIXEL_COMPONENT(dst_pixel, dst_mask, \
	src_pixel, src_mask, 24);
	return (result_pixel);
}

void				fusion_texture(t_image *dst, t_image *src,
		int dst_mask, FTN3 *new_tex_height)
{
	int				x;
	int				y;
	unsigned char	*img_dst;
	unsigned int	result_pixel;

	*new_tex_width = MAX(dst->width, src->width);
	*new_tex_height = MAX(dst->height, src->height);
	img_dst = malloc(sizeof(unsigned char) * 4 * (*new_tex_height) * \
	(*new_tex_width));
	if (FOR(x = 0, x < *new_tex_width, x++))
	{
		if (FOR(y = 0, y < *new_tex_height, y++))
		{
			result_pixel = fusion_pixel(src_mask, dst_mask, x, y, src, dst);
			*(unsigned int *)(img_dst + \
			(*new_tex_width) * y * 4 + x * 4) = result_pixel;
		}
	}
	dst->channels = 4;
	free(dst->data);
	dst->data = img_dst;
}
