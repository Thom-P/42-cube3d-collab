/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_2D_scene.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 19:19:09 by tplanes           #+#    #+#             */
/*   Updated: 2023/03/20 17:31:49 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static inline void	put_pixel(t_image *im, int i, int j, int color);

void	create_map2d(t_imat *map2d, t_input *input, t_meta *meta)
{
	int	i;
	int	j;

	map2d -> m = input -> m * PIX_PER_BLOCK;
	map2d -> n = input -> n * PIX_PER_BLOCK;
	map2d -> imat = (int *)malloc((size_t)map2d -> m
			* (size_t)map2d -> n * sizeof(int));
	if (map2d -> imat == NULL)
		free_and_exit("In create map2d", meta);
	i = 0;
	while (i < map2d -> m)
	{
		j = 0;
		while (j < map2d -> n)
		{
			if (input -> map[i / PIX_PER_BLOCK][j / PIX_PER_BLOCK] == 0)
				map2d -> imat[i * map2d -> n + j] = 0;
			else
				map2d -> imat[i * map2d -> n + j] = WHITE;
			j++;
		}
		i++;
	}
	return ;
}

void	mat2im(t_imat *mat, t_image *im)
{
	int	i;
	int	j;

	i = 0;
	while (i < mat -> m)
	{
		j = 0;
		while (j < mat -> n)
		{
			if (i % PIX_PER_BLOCK == 0 || j % PIX_PER_BLOCK == 0)
				put_pixel(im, i, j, (100 << 16) + (100 << 8) + 100);
			else
				put_pixel(im, i, j, mat -> imat[i * mat -> n + j]);
			j++;
		}
		i++;
	}
	return ;
}

void	draw_player_im(t_player *play, t_image *im)
{
	int	color;
	int	i;
	int	j;
	int	width;

	width = 10;
	i = play -> y - width / 2;
	color = 255;
	while (i < play -> y + width / 2)
	{
		j = play -> x - width / 2;
		while (j < play -> x + width / 2)
			put_pixel(im, i, j++, color);
		i++;
	}
	i = 0;
	while (i < 2 * width)
	{
		put_pixel(im, (int)round(play -> y + (float)i * sinf(play -> theta)),
			(int)round(play -> x + (float)i * cosf(play -> theta)), 255);
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
