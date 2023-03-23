/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 15:13:52 by tplanes           #+#    #+#             */
/*   Updated: 2023/03/23 14:40:52 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	init_hooks(t_meta *meta)
{
	mlx_hook(meta -> xp.win, KEY_DOWN, 0, &key_down_hook, meta);
	mlx_hook(meta -> xp.win, KEY_UP, 0, &key_up_hook, meta);
	mlx_hook(meta -> xp.win, MOUSE_MOVE, 0, &mouse_hook, meta);
	mlx_hook(meta -> xp.win, DESTROY_WIN, 0, &destroy_hook, meta);
	if (SHOW_RAYS)
	{	
		mlx_hook(meta -> xp.win2, DESTROY_WIN, 0, &destroy_hook, meta);
		mlx_hook(meta -> xp.win2, KEY_DOWN, 0, &key_down_hook, meta);
		mlx_hook(meta -> xp.win2, KEY_UP, 0, &key_up_hook, meta);
	}
	mlx_loop_hook(meta -> xp.mlx, &update_and_render, meta);
	return ;
}

// Called on every keyboard down press
int	key_down_hook(int key, t_meta *meta)
{
	if (key == ESCAPE_KEY)
		destroy_hook(meta);
	if (key == M_KEY)
		meta -> flag_minimap ^= 1;
	if (key == N_KEY)
		meta -> flag_mouse_on ^= 1;
	else if (key == SPACE_KEY)
		try_switch_door(meta);
	if (key >= 0 && key < 256)
		meta -> keys_down[key] = 1;
	return (0);
}

// Called on every key release
int	key_up_hook(int key, t_meta *meta)
{
	if (key >= 0 && key < 256)
		meta -> keys_down[key] = 0;
	return (0);
}

int	mouse_hook(int x, int y, t_meta *meta)
{
	float	*theta_p;
	float	d_theta_p;
	float	dx;

	(void) y;
	theta_p = &meta -> play.theta;
	d_theta_p = meta -> play.d_theta;
	dx = (float)x - (float)WIN_NX / 2;
	if (fabsf(dx) < (float)WIN_NX / 8)
	{
		meta -> keys_down[MOUSE_LEFT] = 0;
		meta -> keys_down[MOUSE_RIGHT] = 0;
		return (0);
	}
	else if (dx < 0)
		meta -> keys_down[MOUSE_LEFT]
			= (char)((dx / (-(float)WIN_NX / 2)) * 20);
	else if (dx > 0)
		meta -> keys_down[MOUSE_RIGHT]
			= (char)((dx / ((float)WIN_NX / 2)) * 20);
	return (0);
}

// Called when closing window or pressing escape key
int	destroy_hook(t_meta *meta)
{
	mlx_destroy_image(meta -> xp.mlx, meta -> im.id);
	mlx_destroy_window(meta -> xp.mlx, meta -> xp.win);
	if (SHOW_RAYS)
	{
		mlx_destroy_image(meta -> xp.mlx, meta -> im2.id);
		mlx_destroy_window(meta -> xp.mlx, meta -> xp.win2);
	}
	free_and_exit(NULL, meta);
	return (0);
}
