/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 12:32:20 by tplanes           #+#    #+#             */
/*   Updated: 2023/03/23 13:12:31 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	set_closest_wall(t_raycast *ray, t_player *play, t_input *inp);

//static void	get_h_wall(float th_ray, float *h_d, t_fpt2 *h_wall, t_meta *meta);
static void	get_h_wall(t_raycast *ray, t_meta *meta);

//static void	get_v_wall(float th_ray, float *v_d, t_fpt2 *v_wall, t_meta *meta);
static void	get_v_wall(t_raycast *ray, t_meta *meta);

//static int	is_wall_found(t_fpt2 *wall, t_fpt2 *offset, t_input *inp);
static int	is_wall_found(t_raycast *ray, t_fpt2 *offset, t_input *inp, char h_or_v);

/*
v_dist (h_dist) is the distance to the closest vertical (horizontal) 
wall (if reachable), at vector positions v_wall (h_wall). 
v_dist and h_dist are set to high values by default in case wall not reachable.
*/
void	compute_rays(t_input *inp, t_player *play, t_meta *meta)
{
	t_raycast	ray;

	ray.p0.x = play -> x;
	ray.p0.y = play -> y;
	ray.i = -1;
	while (++ray.i < N_RAY)
	{
		ray.v_dist = (inp -> m + inp -> n) * PIX_PER_BLOCK;
		ray.h_dist = (inp -> m + inp -> n) * PIX_PER_BLOCK;
		ray.theta_ray = play -> theta - FOV / 2 + FOV / (N_RAY - 1) * ray.i;
		if (ray.theta_ray < 0)
			ray.theta_ray += 2 * PI;
		else if (ray.theta_ray > 2 * PI)
			ray.theta_ray = fmodf(ray.theta_ray, 2 * PI);
		//get_h_wall(ray.theta_ray, &ray.h_dist, &ray.h_wall, meta);
		get_h_wall(&ray, meta);
		//get_v_wall(ray.theta_ray, &ray.v_dist, &ray.v_wall, meta);
		get_v_wall(&ray, meta);
		set_closest_wall(&ray, play, inp);
		if (SHOW_RAYS)
			draw_line_image(&ray.p0, &ray.p1, &meta -> im2, 255 << 16);
		draw_column(ray.i, ray.wall_dist, ray.ptr_text, meta);
	}
	return ;
}

/*
off: offset vector to next possible wall intersection
theta > pi means looking up (else looking down)
For first intersection, y-eps to find wall in future casting to int, 
because wall one pix behind multiple of PixPerBlock.
*/
//static void	get_h_wall(float th_ray, float *h_d, t_fpt2 *h_wall, t_meta *meta)
static void	get_h_wall(t_raycast *ray, t_meta *meta)
{
	t_fpt2		off;
	float		itan;
	t_player	*p;

	p = &meta -> play;
	itan = 1.0f / tanf(ray -> theta_ray);
	if (ray -> theta_ray > PI)
	{	
		ray -> h_wall.y = (p -> y / PIX_PER_BLOCK) * PIX_PER_BLOCK - 0.001f;
		off.y = -PIX_PER_BLOCK;
	}
	else
	{
		ray -> h_wall.y = (p -> y / PIX_PER_BLOCK + 1) * PIX_PER_BLOCK;
		off.y = PIX_PER_BLOCK;
	}
	ray -> h_wall.x = p -> x + (ray -> h_wall.y - p -> y) * itan;
	off.x = off.y * itan;
	if (is_wall_found(ray, &off, &meta -> input, 'h'))
		ray -> h_dist = sqrtf(powf(ray -> h_wall.x - (float)p -> x, 2)
				+ powf(ray -> h_wall.y - (float)p -> y, 2));
	return ;
}

/*
off: offset vector to next possible wall intersection
theta > pi/2 and < 3pi/2 means looking left (else looking right)
For first intersection, x-eps to find wall in future casting to int, 
because wall one pix behind multiple of PixPerBlock.
*/
//static void	get_v_wall(float th_ray, float *v_d, t_fpt2 *v_wall, t_meta *meta)
static void	get_v_wall(t_raycast *ray, t_meta *meta)
{
	t_fpt2		off;
	float		tan;
	t_player	*p;

	p = &meta -> play;
	tan = tanf(ray -> theta_ray);
	if (ray -> theta_ray > PI / 2 && ray -> theta_ray < 3 * PI / 2)
	{	
		ray -> v_wall.x = (p -> x / PIX_PER_BLOCK) * PIX_PER_BLOCK - 0.001f;
		off.x = -PIX_PER_BLOCK;
	}
	else
	{
		ray -> v_wall.x = (p -> x / PIX_PER_BLOCK + 1) * PIX_PER_BLOCK;
		off.x = PIX_PER_BLOCK;
	}	
	ray -> v_wall.y = p -> y + (ray -> v_wall.x - p -> x) * tan;
	off.y = off.x * tan;
	if (is_wall_found(ray, &off, &meta -> input, 'v'))
		ray -> v_dist = sqrtf(powf(ray -> v_wall.x - (float)p -> x, 2)
				+ powf(ray -> v_wall.y - (float)p -> y, 2));
	return ;
}

// Increase ray until finds wall intersection or get outta map
static int	is_wall_found(t_raycast *ray, t_fpt2 *offset, t_input *inp, char h_or_v)
{
	int		i;
	int		j;
	t_fpt2	*wall;
	int		*is_door;

	if (h_or_v == 'h')
	{	
		wall = &ray -> h_wall;
		is_door = &ray -> is_h_door;
	}
	else
	{
		wall = &ray -> v_wall;
		is_door = &ray -> is_v_door;
	}
	*is_door = 0;
	while (1)
	{
		i = (int)wall -> y / PIX_PER_BLOCK;
		j = (int)wall -> x / PIX_PER_BLOCK;
		if (i < 0 || i > inp -> m - 1 || j < 0 || j > inp -> n -1)
			break ;
		if (inp -> map[i * inp -> n + j] == '1' || inp -> map[i * inp -> n + j] == '2')
		{
			if (inp -> map[i * inp -> n + j] == '2')
				*is_door = 1;
			return (1);
		}
		wall -> y += offset -> y;
		wall -> x += offset -> x;
	}
	return (0);
}

/*
add horizontal offset to texture ptr
sometimes seems like glitchy column appears,
probably happens when ray hits a corner
*/
static void	set_closest_wall(t_raycast *ray, t_player *play, t_input *inp)
{
	if (ray -> h_dist < ray -> v_dist)
	{
		ray -> p1.x = (int)round(ray -> h_wall.x);
		ray -> p1.y = (int)round(ray -> h_wall.y);
		ray -> wall_dist = ray -> h_dist
			* cosf(fabsf(ray -> theta_ray - play -> theta));
		if (ray -> theta_ray > PI && !ray -> is_h_door)
			ray -> ptr_text = (int *)(inp -> textures[SO].addr) + ray -> p1.x % PIX_PER_BLOCK;
		else if (ray -> theta_ray > PI)
			ray -> ptr_text = (int *)(inp -> textures[4].addr) + ray -> p1.x % PIX_PER_BLOCK;
		else if (!ray -> is_h_door)
			ray -> ptr_text = (int *)(inp -> textures[NO].addr)
				+ PIX_PER_BLOCK - 1 - (ray -> p1.x % PIX_PER_BLOCK);
		else
			ray -> ptr_text = (int *)(inp -> textures[4].addr)
				+ PIX_PER_BLOCK - 1 - (ray -> p1.x % PIX_PER_BLOCK);
	}
	else
	{
		ray -> p1.x = (int)round(ray -> v_wall.x);
		ray -> p1.y = (int)round(ray -> v_wall.y);
		ray -> wall_dist = ray -> v_dist
			* cosf(fabsf(ray -> theta_ray - play -> theta));
		if ((ray -> theta_ray < 0.5 * PI || ray -> theta_ray > 1.5 * PI) && !ray -> is_v_door)
			ray -> ptr_text = (int *)(inp -> textures[WE].addr) + ray -> p1.y % PIX_PER_BLOCK;
		else if (ray -> theta_ray < 0.5 * PI || ray -> theta_ray > 1.5 * PI)
			ray -> ptr_text = (int *)(inp -> textures[4].addr) + ray -> p1.y % PIX_PER_BLOCK;
		else if (!ray -> is_v_door)
			ray -> ptr_text = (int *)(inp -> textures[EA].addr)
				+ PIX_PER_BLOCK - 1 - (ray -> p1.y % PIX_PER_BLOCK);
		else
			ray -> ptr_text = (int *)(inp -> textures[4].addr)
				+ PIX_PER_BLOCK - 1 - (ray -> p1.y % PIX_PER_BLOCK);
	}
	return ;
}
/*
static inline float dist(float x0, float y0, float x1, float y1)
{
	return (sqrtf(powf(x1 - x0, 2) + powf(y1 - y0, 2)));
}

void	draw_box_around_image(t_image *im)
{	
	int	i;

	i = 0;
	while (i < im -> nx)
	{
		f_put_pixel(im, 0, i, WHITE);
		f_put_pixel(im, im -> ny - 1, i, WHITE);
		i++;
	}
	i = 0;
	while (i < im -> ny)
	{
		f_put_pixel(im, i, 0, WHITE);
		f_put_pixel(im, i, im -> nx - 1, WHITE);
		i++;
	}
	return ;
}*/
