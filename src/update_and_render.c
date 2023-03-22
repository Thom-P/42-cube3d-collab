/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_and_render.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 11:37:00 by tplanes           #+#    #+#             */
/*   Updated: 2023/03/21 17:52:38 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	update_position(t_player *play, char *keys_down);

static int	is_any_key_down(char *keys_down);

/*
Two step check to allow wall slide
*/
int	update_and_render(t_meta *meta)
{	
	t_player	*p;
	char		**map;
	char		*keys_down;
	int			x_save;
	int			y_save;

	p = &meta -> play;
	map = meta -> input.map;
	keys_down = meta -> keys_down;
	if (is_any_key_down(keys_down) == 0)
		return (0);
	x_save = p -> x;
	y_save = p -> y;
	if (keys_down[LEFT_ARROW_KEY])
		p -> theta = fmodf(p -> theta + (2 * PI - p -> d_theta), 2 * PI);
	else if (keys_down[RIGHT_ARROW_KEY])
		p -> theta = fmodf(p -> theta + p -> d_theta, 2 * PI);
	update_position(p, keys_down);
	if (map[y_save / PIX_PER_BLOCK][p -> x / PIX_PER_BLOCK] != 0)
		p -> x = x_save;
	if (map[p -> y / PIX_PER_BLOCK][p -> x / PIX_PER_BLOCK] != 0)
		p -> y = y_save;
	render(meta);
	return (0);
}

static void	update_position(t_player *p, char *keys_down)
{
	if (keys_down[A_KEY])
	{
		p -> x += (int)round((float)p -> step * cosf(p -> theta - PI / 2));
		p -> y += (int)round((float)p -> step * sinf(p -> theta - PI / 2));
	}
	else if (keys_down[D_KEY])
	{
		p -> x -= (int)round((float)p -> step * cosf(p -> theta - PI / 2));
		p -> y -= (int)round((float)p -> step * sinf(p -> theta - PI / 2));
	}
	if (keys_down[W_KEY] || keys_down[UP_ARROW_KEY])
	{
		p -> x += (int)round((float)p -> step * cosf(p -> theta));
		p -> y += (int)((float)p -> step * sinf(p -> theta));
	}
	else if (keys_down[S_KEY] || keys_down[DOWN_ARROW_KEY])
	{	
		p -> x -= (int)round((float)p -> step * cosf(p -> theta));
		p -> y -= (int)round((float)p -> step * sinf(p -> theta));
	}
	return ;
}

//draw_box_around_image(&meta -> im);
//2D and 3D render
void	render(t_meta *meta)
{
	if (SHOW_RAYS)
		mat2im(&meta -> map2d, &meta -> im2);
	compute_rays(&meta -> input, &meta -> play, meta);
	if (meta -> flag_minimap == 1)
		draw_minimap(meta);
	mlx_put_image_to_window(meta -> xp.mlx, meta -> xp.win,
		meta -> im.id, meta -> im.pos_x, meta -> im.pos_y);
	mlx_destroy_image(meta -> xp.mlx, meta -> im.id);
	create_image(meta);
	if (SHOW_RAYS)
	{
		draw_player_im(&meta -> play, &meta -> im2);
		mlx_put_image_to_window(meta -> xp.mlx, meta -> xp.win2,
			meta -> im2.id, meta -> im2.pos_x, meta -> im2.pos_y);
		mlx_destroy_image(meta -> xp.mlx, meta -> im2.id);
		create_2d_image(meta);
	}
	return ;
}

static int	is_any_key_down(char *keys_down)
{
	int	i;

	i = -1;
	while (++i < 256)
	{
		if (keys_down[i])
			return (1);
	}
	return (0);
}
