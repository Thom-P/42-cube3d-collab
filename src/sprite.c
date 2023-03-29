/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 09:56:31 by tplanes           #+#    #+#             */
/*   Updated: 2023/03/29 14:25:55 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	draw_sprite(int i_ray_cent, t_text_map *smap, double x_dtext, t_meta *meta);

static void draw_pix_group(t_image *im, int i, int i_ray, int color);

void update_sprite(t_player *p, t_sprite *sp, t_meta *meta)
{
	t_text_map	smap;
	double		x_dtext;
	int			i_ray_cent;

	sp->x = 1696;
	sp->y = 736;
	sp->dx = sp->x - p->x; 
	sp->dy = sp->y - p->y;
	sp->cost = cosf(p->theta);
	sp->sint = sinf(p->theta);
	sp->dist = sp->dx*sp->cost + sp->dy*sp->sint; //effective distance of sprite
	if (sp->dist == 0)
		return ;
	sp->offset = sp->dx * -sp->sint + sp->dy * sp->cost;
	i_ray_cent = N_RAY / 2 + (int)(sp->offset / sp->dist * (float)(D_P2P / INTERP_FACT));	
	sp->h = (int)round((float)SP_SIZE / sp->dist * (float)D_P2P);
	sp->w = (int)round((float)SP_SIZE / sp->dist * (float)(D_P2P / INTERP_FACT));
	if (sp->h > IM3_NY)
		return ;
	smap.dtext = (double)SP_SIZE / (double)sp->h;
	x_dtext = (double)SP_SIZE / (double)sp->w;
	draw_sprite(i_ray_cent, &smap, x_dtext, meta);
	return ;
}
/*
float theta_s = atan2f(sp->dy, sp->dx);
float dtheta_s;
if (theta_s < 0)
	theta_s = 2 * PI + theta_s;
dtheta_s = theta_s - p->theta;
int i_ray_cent = (int)(dtheta_s / (FOV / 2) * (float)(N_RAY - 1) / 2) + N_RAY / 2;
*/

static void	draw_sprite(int i_ray_cent, t_text_map *smap, double x_dtext, t_meta *meta)
{
	int		i_ray;
	int		i;
	int		color;
	double	x_text_offset;
	t_sprite *sp;

	sp = &meta -> sp;
	x_text_offset = 0;
	i_ray = i_ray_cent - sp->w / 2 - 1;
	while (++i_ray < i_ray_cent + sp->w / 2)
	{
		if (i_ray < 0 || i_ray > N_RAY - 1 || meta->dist_col[i_ray] < sp->dist)
		{	
			x_text_offset += x_dtext;
			continue ;
		}
		smap->ptr_text = (int *)(meta -> input.textures[4].addr) + (int)x_text_offset;
		smap->text_offset = 0;
		i = (IM3_NY - sp->h) / 2 - 1;
		while (++i < (IM3_NY + sp->h) / 2)
    	{
       		color = *(smap->ptr_text + (int)(smap->text_offset) * TEXT_SIZE);
       		if (color != (255 << 16) + 255)
				draw_pix_group(&meta->im, i, i_ray, color);
       		smap->text_offset += smap->dtext;
    	}
		x_text_offset += x_dtext;
	}	
	return ;
}

static void draw_pix_group(t_image *im, int i, int i_ray, int color)
{
    char    *pix_addr;
    int     j;
    int     k;

    k = -1;
    while (++k < INTERP_FACT)
    {
        j = i_ray * INTERP_FACT + k;
        pix_addr = im -> addr + i * im -> line_size + j * (im -> bpp / 8);
        *((unsigned int *)pix_addr) = (unsigned int)color;
    }
    return ;
}
