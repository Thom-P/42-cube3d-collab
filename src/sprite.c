/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 09:56:31 by tplanes           #+#    #+#             */
/*   Updated: 2023/03/29 12:29:19 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void draw_pix_group(t_image *im, int i, int i_ray, int color);

void update_sprite(t_player *p, t_sprite *sp, t_meta *meta)
{

	t_text_map smap;
	
	sp->x = 1696;
	sp->y = 736;
	sp->dx = sp->x - p->x; 
	sp->dy = sp->y - p->y;
		
	float cost = cosf(p->theta);
	float sint = sinf(p->theta);

	float dist = sp->dx*cost + sp->dy*sint; //effective distance of sprite
	//float offset = sp->dx * -sint + sp->dy * cost;
	//int i_ray = N_RAY / 2 + (int)offset;
	
	float theta_s = atan2f(sp->dy, sp->dx);
	
	float dtheta_s;
	if (theta_s < 0)
		theta_s = 2 * PI + theta_s;
	dtheta_s = theta_s - p->theta;
		
	int i_ray_center = (int)(dtheta_s / (FOV / 2) * (float)(N_RAY - 1) / 2) + N_RAY / 2;

	int sp_size = 32;	
	int h = (int)round((float)sp_size / dist * (float)D_P2P);
	int w = (int)round((float)sp_size / dist * (float)(D_P2P / INTERP_FACT));
	if (h > IM3_NY)
		return ;
	int i;
   	int color;

	//(void)smap;
	
	smap.dtext = (double)sp_size / (double)h;
	double x_text_offset = 0;
	double x_dtext = (double)sp_size / (double)w;

	int i_ray = i_ray_center - w / 2;
	while (i_ray < i_ray_center + w / 2)
	{
		
		if (i_ray < 0 || i_ray > N_RAY - 1 || meta->dist_col[i_ray] < dist)
		{	
			i_ray++;
			x_text_offset += x_dtext;
			continue ;
		}
		
		smap.ptr_text = (int *)(meta -> input.textures[4].addr) + (int)x_text_offset;


		smap.text_offset = 0;
		i = (IM3_NY - h) / 2;
		while (i < (IM3_NY + h) / 2)
    	{
       		//color = WHITE;
       		color = *(smap.ptr_text + (int)(smap.text_offset) * TEXT_SIZE);
       		draw_pix_group(&meta->im, i, i_ray, color);
       		smap.text_offset += smap.dtext;
       		i++;
    	}
		i_ray++;
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
