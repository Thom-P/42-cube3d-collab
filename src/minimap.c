/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:33:01 by tplanes           #+#    #+#             */
/*   Updated: 2023/03/23 15:21:08 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static inline void	put_pixel(t_image *im, int i, int j, int color);

static void		draw_player_in_minimap(t_meta *meta, int ppb_mp, int width);

static int		get_ppb_minimap(int m, int n);

//ppb_mp: pixels per blocks in minimap
//ind[3] holds indexes i, j, and ind_lin
void	draw_minimap(t_meta *meta)
{
	int	ppb_mp;
	int	ind[3];

	ppb_mp = get_ppb_minimap(meta -> input.m, meta -> input.n);
	ind[0] = -1;
	while (++ind[0] < meta -> input.m * ppb_mp)
	{
		ind[1] = -1;
		while (++ind[1] < meta -> input.n * ppb_mp)
		{
			ind[2] = ind[0] / ppb_mp * meta -> input.n + ind[1] / ppb_mp;
			if (meta -> input.map[ind[2]] == '0')
				put_pixel(&meta -> im, ind[0], ind[1], 3289650);
			else if (meta -> input.map[ind[2]] == '1')
				put_pixel(&meta -> im, ind[0], ind[1], WHITE);
			else if (meta -> input.map[ind[2]] == '2')
				put_pixel(&meta -> im, ind[0], ind[1], 255);
			else if (meta -> input.map[ind[2]] == '3')
				put_pixel(&meta -> im, ind[0], ind[1], 255 / 2);
			else
				put_pixel(&meta -> im, ind[0], ind[1], 0);
		}
	}
	draw_player_in_minimap(meta, ppb_mp, ppb_mp / 4);
	return ;
}

// Returns number of pixel per block in minimap
static int	get_ppb_minimap(int m, int n)
{
	int	ppb_mp;

	if ((WIN_NY / 4) / m < (WIN_NX / 4) / n)
		ppb_mp = (WIN_NY / 4) / m;
	else
		ppb_mp = (WIN_NX / 4) / n;
	return (ppb_mp);
}

static void	draw_player_in_minimap(t_meta *meta, int ppb_mp, int width)
{
	t_image		*im;
	t_ipt2		p;
	int			i;
	int			j;

	im = &meta -> im;
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

static inline void	put_pixel(t_image *im, int i, int j, int color)
{
	char	*pix_addr;

	pix_addr = im -> addr + i * im -> line_size + j * (im -> bpp / 8);
	*((unsigned int *)pix_addr) = (unsigned int)color;
	return ;
}
