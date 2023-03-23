/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:33:01 by tplanes           #+#    #+#             */
/*   Updated: 2023/03/23 10:55:06 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static inline void  put_pixel(t_image *im, int i, int j, int color);

static void			draw_player_in_minimap(t_meta *meta, int ppb_mp);

//ppb_mp: pixels per blocks in minimap
void	draw_minimap(t_meta *meta)
{
	int	ppb_mp;
	int	i;
	int	j;
	
	if ((WIN_NY / 4) / meta -> input.m < (WIN_NX / 4) / meta -> input.n)
		ppb_mp = (WIN_NY / 4) / meta -> input.m;
	else
		ppb_mp = (WIN_NX / 4) / meta -> input.n;
	i = -1;
	while (++i < meta -> input.m * ppb_mp)
	{
		j = -1;
		while (++j < meta -> input.n * ppb_mp)
		{
			if (meta -> input.map[i / ppb_mp * meta -> input.n + j / ppb_mp] == '0')
    			put_pixel(&meta -> im, i, j, 50 << 16 | 50 << 8 | 50);
			if (meta -> input.map[i / ppb_mp * meta -> input.n + j / ppb_mp] == '1')
    			put_pixel(&meta -> im, i, j, WHITE);
			else if (meta -> input.map[i / ppb_mp * meta -> input.n + j / ppb_mp] == '2')
    			put_pixel(&meta -> im, i, j, 255);
			else if (meta -> input.map[i / ppb_mp * meta -> input.n + j / ppb_mp] == '3')
    			put_pixel(&meta -> im, i, j, 255 / 2);
			else
    			put_pixel(&meta -> im, i, j, 0);
		}
	}
	draw_player_in_minimap(meta, ppb_mp);
	return ;
}

static void	draw_player_in_minimap(t_meta *meta, int ppb_mp)
{
	t_image		*im;
	int			width;
	t_ipt2		p;
	int			i;
	int			j;

	im = &meta -> im;
	width = ppb_mp / 4;
	p.x = (int)((float)meta -> play.x / (float)PIX_PER_BLOCK * (float)ppb_mp);
	p.y = (int)((float)meta -> play.y / (float)PIX_PER_BLOCK * (float)ppb_mp);
	i = p.y - width / 2;
	while (i < p.y + width / 2)
	{
		j = p.x - width / 2;
		while (j < p.x + width / 2)
			put_pixel(im, i, j++, 255 << 16);
		i++;
	}
	i = 0;
	while (i < 2 * width)
	{
		put_pixel(im, (int)round(p.y + (float)i * sinf(meta -> play.theta)),
			(int)round(p.x + (float)i * cosf(meta -> play.theta)), 255 << 16);
		i++;
	}
	return ;
}

static inline void  put_pixel(t_image *im, int i, int j, int color)
{
	char    *pix_addr;

	pix_addr = im -> addr + i * im -> line_size + j * (im -> bpp / 8);
	*((unsigned int *)pix_addr) = (unsigned int)color;
	return ;
}
