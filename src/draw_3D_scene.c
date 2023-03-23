/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3D_scene.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 11:46:22 by tplanes           #+#    #+#             */
/*   Updated: 2023/03/23 14:38:18 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	draw_ceil(t_image *im, int i_ray, int i_wall_top, int ceil_color);

static void	draw_wall(t_image *im, int i_ray, int h, t_text_map *tmap);

static void	draw_floor(t_image *im, int i_ray, int i_wall_bot, int floor_color);

static void	draw_pix_group(t_image *im, int i, int i_ray, int color);

/*
True wall height h computed by rule of three using 
distance from player to projection plane D_P2P.
Then used to get starting offset in texture (text_offset), 
and step through texture (dtext).
h then clipped to screen height.
*/
void	draw_column(int i_ray, float wall_dist, int *ptr_text, t_meta *meta)
{
	int			h;
	int			ind_wall_top;
	t_text_map	tmap;

	h = (int)round((float)PIX_PER_BLOCK / wall_dist * (float)D_P2P);
	tmap.dtext = (double)TEXT_SIZE / (double)h;
	tmap.text_offset = 0.0;
	tmap.ptr_text = ptr_text;
	if (h > IM3_NY)
	{
		tmap.text_offset = 0.5 * ((double)(h - IM3_NY)) * tmap.dtext;
		h = IM3_NY;
	}
	ind_wall_top = (IM3_NY - h) / 2;
	draw_ceil(&meta -> im, i_ray, ind_wall_top, meta -> input.ceiling);
	draw_wall(&meta -> im, i_ray, h, &tmap);
	draw_floor(&meta -> im, i_ray, ind_wall_top + h - 1, meta -> input.floor);
	return ;
}

static void	draw_ceil(t_image *im, int i_ray, int ind_wall_top, int ceil_color)
{
	int	i;

	i = -1;
	while (++i < ind_wall_top)
		draw_pix_group(im, i, i_ray, ceil_color);
	return ;
}

/* Fetch the correct pixel in the texture by stepping dtext down */
static void	draw_wall(t_image *im, int i_ray, int h, t_text_map *tmap)
{
	int	i;
	int	color;

	i = (IM3_NY - h) / 2;
	while (i < (IM3_NY + h) / 2)
	{	
		color = *(tmap -> ptr_text + (int)(tmap -> text_offset) * TEXT_SIZE);
		draw_pix_group(im, i, i_ray, color);
		tmap -> text_offset += tmap -> dtext;
		i++;
	}
	return ;
}

static void	draw_floor(t_image *im, int i_ray, int i_wall_bot, int floor_color)
{
	int	i;

	i = i_wall_bot;
	while (++i < IM3_NY)
		draw_pix_group(im, i, i_ray, floor_color);
	return ;
}

/* Replicate each column to extend 320*200 resolution INTERP_FACT times */
static void	draw_pix_group(t_image *im, int i, int i_ray, int color)
{
	char	*pix_addr;
	int		j;
	int		k;

	k = -1;
	while (++k < INTERP_FACT)
	{
		j = i_ray * INTERP_FACT + k;
		pix_addr = im -> addr + i * im -> line_size + j * (im -> bpp / 8);
		*((unsigned int *)pix_addr) = (unsigned int)color;
	}
	return ;
}
