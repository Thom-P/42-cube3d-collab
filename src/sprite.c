/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 09:56:31 by tplanes           #+#    #+#             */
/*   Updated: 2023/03/29 10:26:28 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void draw_pix_group(t_image *im, int i, int i_ray, int color);

void update_sprite(t_player *p, t_sprite *sp, t_meta *meta)
{

	(void)meta;
	sp->x = 1696;
	sp->y = 736;
	sp->dx = sp->x - p->x; 
	sp->dy = sp->y - p->y;
	if (fabsf(sp->dx) < 5 || fabsf(sp->dy) < 5)
		return ;
		
	float cost = cosf(p->theta);
	float sint = sinf(p->theta);

	float dist = sp->dx*cost + sp->dy*sint; //effective distance of sprite
	//float offset = sp->dx * -sint + sp->dy * cost;
	//int i_ray = N_RAY / 2 + (int)offset;
	
	float theta_s = atanf(sp->dy/sp->dx);
	int i_ray = (int)((theta_s - p->theta) / (FOV / 2) * (float)(N_RAY - 1) / 2) + N_RAY / 2;

	if (i_ray < 0 || i_ray > N_RAY - 1)
		return ;
	
	int h = (int)round((float)PIX_PER_BLOCK / dist * (float)D_P2P);
	if (h > IM3_NY)
		return ;
	int i = (IM3_NY - h) / 2;
    int color;
	while (i < (IM3_NY + h) / 2)
    {
        color = WHITE;//*(tmap -> ptr_text + (int)(tmap -> text_offset) * TEXT_SIZE);
        draw_pix_group(&meta->im, i, i_ray, color);
        //tmap -> text_offset += tmap -> dtext;
        i++;
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
