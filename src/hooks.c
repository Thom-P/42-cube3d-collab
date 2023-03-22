/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 15:13:52 by tplanes           #+#    #+#             */
/*   Updated: 2023/03/21 17:57:27 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	init_hooks(t_meta *meta)
{
	mlx_hook(meta -> xp.win, KEY_DOWN, 0, &key_down_hook, meta);
	mlx_hook(meta -> xp.win, KEY_UP, 0, &key_up_hook, meta);
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
	if (key == SPACE_KEY)
		meta -> flag_minimap ^= 1;
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
