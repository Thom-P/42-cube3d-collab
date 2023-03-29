/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_and_render.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 11:37:00 by tplanes           #+#    #+#             */
/*   Updated: 2023/03/29 14:57:22 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	update_position(t_player *play, char *keys_down);

static void	update_rotation(int flag_mouse_on, t_player *p, char *keys_down);

static int	is_any_key_down(char *keys_down);

/*
Two step check to allow wall slide
*/
int	update_and_render(t_meta *meta)
{	
	t_player	*p;
	char		*map;
	char		*keys_down;
	int			pos_save[2];
	int			ind_lin;

	p = &meta -> play;
	map = meta -> input.map;
	keys_down = meta -> keys_down;
	if (is_any_key_down(keys_down) == 0)
		return (0);
	pos_save[0] = p -> x;
	pos_save[1] = p -> y;
	update_rotation(meta -> flag_mouse_on, p, keys_down);
	update_position(p, keys_down);
	ind_lin = pos_save[1] / PIX_PER_BLOCK * meta -> input.n
		+ p -> x / PIX_PER_BLOCK;
	if (map[ind_lin] == '1' || map[ind_lin] == '2')
		p -> x = pos_save[0];
	ind_lin = p -> y / PIX_PER_BLOCK * meta -> input.n + p -> x / PIX_PER_BLOCK;
	if (map[ind_lin] == '1' || map[ind_lin] == '2')
		p -> y = pos_save[1];
	render(meta);
	return (0);
}

static void	update_rotation(int flag_mouse_on, t_player *p, char *keys_down)
{
	if (!flag_mouse_on && keys_down[LEFT_ARROW_KEY])
		p -> theta = fmodf(p -> theta + (2 * PI - p -> d_theta), 2 * PI);
	else if (!flag_mouse_on && keys_down[RIGHT_ARROW_KEY])
		p -> theta = fmodf(p -> theta + p -> d_theta, 2 * PI);
	else if (flag_mouse_on && keys_down[MOUSE_LEFT])
		p -> theta = fmodf(p -> theta + (2 * PI - p -> d_theta_mouse
					* (float)keys_down[MOUSE_LEFT]), 2 * PI);
	else if (flag_mouse_on && keys_down[MOUSE_RIGHT])
		p -> theta = fmodf(p -> theta
				+ p -> d_theta_mouse * (float)keys_down[MOUSE_RIGHT], 2 * PI);
	return ;
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
		p -> y += (int)round((float)p -> step * sinf(p -> theta));
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
	update_sprite(&meta -> play, &meta -> sp, meta);
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
