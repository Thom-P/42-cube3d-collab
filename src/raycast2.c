/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:41:12 by saeby             #+#    #+#             */
/*   Updated: 2023/03/29 16:41:35 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/*
add horizontal offset to texture ptr
sometimes seems like glitchy column appears,
probably happens when ray hits a corner
*/
void	set_h_closest_wall(t_raycast *r, t_player *p, t_input *i, float *dist)
{
	r -> p1.x = (int)round(r -> h_wall.x);
	r -> p1.y = (int)round(r -> h_wall.y);
	dist[r -> i] = r -> h_dist;
	r -> wall_dist = r -> h_dist
		* cosf(fabsf(r -> theta_ray - p -> theta));
	if (r -> theta_ray > PI && !r -> is_h_door)
		r -> ptr_text = (int *)(i -> textures[SO].addr)
			+ r -> p1.x % PIX_PER_BLOCK;
	else if (r -> theta_ray > PI)
		r -> ptr_text = (int *)(i -> textures[4].addr)
			+ r -> p1.x % PIX_PER_BLOCK;
	else if (!r -> is_h_door)
		r -> ptr_text = (int *)(i -> textures[NO].addr)
			+ PIX_PER_BLOCK - 1 - (r -> p1.x % PIX_PER_BLOCK);
	else
		r -> ptr_text = (int *)(i -> textures[4].addr)
			+ PIX_PER_BLOCK - 1 - (r -> p1.x % PIX_PER_BLOCK);
	return ;
}

void	set_v_closest_wall(t_raycast *r, t_player *p, t_input *i, float *d)
{
	r -> p1.x = (int)round(r -> v_wall.x);
	r -> p1.y = (int)round(r -> v_wall.y);
	d[r -> i] = r -> v_dist;
	r -> wall_dist = r -> v_dist * cosf(fabsf(r -> theta_ray - p -> theta));
	if ((r -> theta_ray < 0.5 * PI || r -> theta_ray > 1.5 * PI)
		&& !r -> is_v_door)
		r -> ptr_text = (int *)(i -> textures[WE].addr)
			+ r -> p1.y % PIX_PER_BLOCK;
	else if (r -> theta_ray < 0.5 * PI || r -> theta_ray > 1.5 * PI)
		r -> ptr_text = (int *)(i -> textures[4].addr)
			+ r -> p1.y % PIX_PER_BLOCK;
	else if (!r -> is_v_door)
		r -> ptr_text = (int *)(i -> textures[EA].addr)
			+ PIX_PER_BLOCK - 1 - (r -> p1.y % PIX_PER_BLOCK);
	else
		r -> ptr_text = (int *)(i -> textures[4].addr)
			+ PIX_PER_BLOCK - 1 - (r -> p1.y % PIX_PER_BLOCK);
	return ;
}
