/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 15:01:56 by tplanes           #+#    #+#             */
/*   Updated: 2023/03/29 14:37:26 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	create_win(t_meta *meta, int win_ny, int win_nx, char *title);

static void	create_2d_win(t_meta *meta, char *title);

int	main(int ac, char **av)
{
	t_meta	meta;

	if (ac != 2)
	{
		ft_putstr_fd("Incorrect number of arguments (expected 1).\n", 2);
		exit(EXIT_FAILURE);
	}
	init_mem_ptrs(&meta);
	parse_map(av[1], &meta);
	if (SHOW_RAYS)
		create_map2d(&meta.map2d, &meta.input, &meta);
	init_player_and_keys(&meta.play, &meta.input, &meta.sp, meta.keys_down);
	create_win(&meta, WIN_NY, WIN_NX, "***Cube 3D***");
	mlx_string_put(meta.xp.mlx, meta.xp.win, 1, 1, WHITE, "Move: WASD, Rotate: "
		"ARROWS/MOUSE (Toggle with N), Minimap: M, Action: SPACE, Quit: ESC");
	create_image(&meta);
	if (SHOW_RAYS)
	{	
		create_2d_win(&meta, "***2D Map***");
		create_2d_image(&meta);
	}
	render(&meta);
	init_hooks(&meta);
	mlx_loop(meta.xp.mlx);
	return (0);
}

static void	create_win(t_meta *meta, int win_ny, int win_nx, char *title)
{
	void	*mlx;
	void	*win;

	mlx = mlx_init();
	if (mlx == NULL)
		free_and_exit("Error in mlx init", meta);
	meta -> xp.mlx = mlx;
	win = mlx_new_window(mlx, win_nx, win_ny, title);
	if (win == NULL)
		free_and_exit("Error in window init", meta);
	meta -> xp.win = win;
	if (load_textures(meta))
		free_and_exit("Error in loading textures", meta);
	return ;
}

static void	create_2d_win(t_meta *meta, char *title)
{
	void	*win2;

	win2 = mlx_new_window(meta -> xp.mlx, meta -> map2d.n, meta -> map2d.m,
			title);
	if (win2 == NULL)
	{
		mlx_destroy_window(meta -> xp.mlx, meta -> xp.win);
		free_and_exit("Error in window2 init", meta);
	}
	meta -> xp.win2 = win2;
	return ;
}

void	create_image(t_meta *meta)
{
	t_image	*im;

	im = &meta -> im;
	im -> nx = IM3_NX;
	im -> ny = IM3_NY;
	im -> pos_x = (WIN_NX - im -> nx) / 2;
	im -> pos_y = (WIN_NY - im -> ny) / 2;
	im -> id = mlx_new_image(meta -> xp.mlx, im -> nx, im -> ny);
	if (im -> id == NULL)
	{
		mlx_destroy_window(meta -> xp.mlx, meta -> xp.win);
		free_and_exit("Error in image creation", meta);
	}
	im -> addr = mlx_get_data_addr(im -> id, &im -> bpp,
			&im -> line_size, &im -> endian);
	return ;
}

void	create_2d_image(t_meta *meta)
{
	t_image	*im2;

	im2 = &meta -> im2;
	im2 -> nx = meta -> map2d.n;
	im2 -> ny = meta -> map2d.m;
	im2 -> pos_x = 0;
	im2 -> pos_y = 0;
	im2 -> id = mlx_new_image(meta -> xp.mlx, im2 -> nx, im2 -> ny);
	if (im2 -> id == NULL)
	{
		mlx_destroy_image(meta -> xp.mlx, meta -> im.id);
		mlx_destroy_window(meta -> xp.mlx, meta -> xp.win2);
		mlx_destroy_window(meta -> xp.mlx, meta -> xp.win);
		free_and_exit("Error in image creation", meta);
	}
	im2 -> addr = mlx_get_data_addr(im2 -> id, &im2 -> bpp,
			&im2 -> line_size, &im2 -> endian);
	return ;
}
