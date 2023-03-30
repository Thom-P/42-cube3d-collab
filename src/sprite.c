/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 09:56:31 by tplanes           #+#    #+#             */
/*   Updated: 2023/03/30 14:03:34 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	draw_sprite(int ray_ct, t_text_map *smap, t_meta *meta);

static void	draw_pix_group(t_image *im, int i, int i_ray, int color);

static void	move_sprite(t_sprite *sp, t_input *inp, t_meta *meta);

void	update_sprite(t_player *p, t_sprite *sp, t_meta *meta)
{
	t_text_map	smap;
	int			i_ray_cent;

	sp->dx = sp->x - p->x;
	sp->dy = sp->y - p->y;
	sp->cost = cosf(p->theta);
	sp->sint = sinf(p->theta);
	sp->dist_real = sqrtf(sp->dx * sp->dx + sp->dy * sp->dy);
	sp->dist = sp->dx * sp->cost + sp->dy * sp->sint;
	if (fabsf(sp->dist) <= 2)
		return ;
	sp->offset = sp->dx * -sp->sint + sp->dy * sp->cost;
	i_ray_cent = N_RAY / 2
		+ (int)(sp->offset / sp->dist * (float)(D_P2P / INTERP_FACT));
	sp->h = (int)round((float)S_SIZE / sp->dist * (float)D_P2P);
	sp->w = (int)round((float)S_SIZE
			/ sp->dist * (float)(D_P2P / INTERP_FACT));
	if (sp->h > IM3_NY)
		return ;
	smap.dtext = (double)S_SIZE / (double)sp->h;
	smap.x_dtext = (double)S_SIZE / (double)sp->w;
	draw_sprite(i_ray_cent, &smap, meta);
	if (fabsf(sp -> dist_real) > (float)PIX_PER_BLOCK && meta -> flag_bird)
		move_sprite(sp, &meta->input, meta);
	return ;
}
/*
float theta_s = atan2f(sp->dy, sp->dx);
float dtheta_s;
if (theta_s < 0)
	theta_s = 2 * PI + theta_s;
dtheta_s = theta_s - p->theta;
int i_ray_cent = (int)(dtheta_s / (FOV / 2) 
* (float)(N_RAY - 1) / 2) + N_RAY / 2;
*/

static void	move_sprite(t_sprite *sp, t_input *inp, t_meta *meta)
{
	float	step;
	float	theta_s;
	int		pos_save[2];
	int		ind_lin;

	pos_save[0] = sp->x;
	pos_save[1] = sp->y;
	theta_s = atan2f(sp->dy, sp->dx);
	step = (float)meta -> play.step / 3;
	sp -> x += (int)round(-step * cosf(theta_s));
	sp -> y += (int)round(-step * sinf(theta_s));
	ind_lin = pos_save[1] / PIX_PER_BLOCK * meta -> input.n
		+ sp -> x / PIX_PER_BLOCK;
	if (inp -> map[ind_lin] == '1' || inp -> map[ind_lin] == '2')
		sp -> x = pos_save[0];
	ind_lin = sp -> y / PIX_PER_BLOCK
		* meta -> input.n + sp -> x / PIX_PER_BLOCK;
	if (inp -> map[ind_lin] == '1' || inp -> map[ind_lin] == '2')
		sp -> y = pos_save[1];
	return ;
}

static void	draw_sprite(int ray_ct, t_text_map *smap, t_meta *m)
{
	int			i_ray;

	smap->x_text_offset = 0;
	i_ray = ray_ct - m->sp.w / 2 - 1;
	while (++i_ray < ray_ct + m->sp.w / 2)
	{
		if (i_ray < 0 || i_ray > N_RAY - 1 || m->dist_col[i_ray] < m->sp.dist)
		{	
			smap->x_text_offset += smap->x_dtext;
			continue ;
		}
		smap->ptr_text = (int *)(m->input.textures[5].addr)
			+ (int)smap->x_text_offset;
		smap->text_offset = 0;
		smap->i = (IM3_NY - m->sp.h) / 2 - 1;
		while (++smap->i < (IM3_NY + m->sp.h) / 2)
		{
			smap->color = *(smap->ptr_text + (int)(smap->text_offset) * S_SIZE);
			if (smap->color != (255 << 16) + 255)
				draw_pix_group(&m->im, smap->i, i_ray, smap->color);
			smap->text_offset += smap->dtext;
		}
		smap->x_text_offset += smap->x_dtext;
	}	
	return ;
}

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
