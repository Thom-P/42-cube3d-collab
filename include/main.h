/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 15:13:35 by tplanes           #+#    #+#             */
/*   Updated: 2023/03/23 15:26:34 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <math.h>
# include <fcntl.h>

# include "mlx.h"
# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"

//0 (off) or 1 (show extra window window with 2D map and rays) 
# define SHOW_RAYS 0

# define PI (float)M_PI

# define DESTROY_WIN 17  //closing window event
# define KEY_DOWN 2
# define KEY_UP 3
# define MOUSE_MOVE 6

# define ESCAPE_KEY 53
# define LEFT_ARROW_KEY 123
# define RIGHT_ARROW_KEY 124
# define W_KEY 13
# define A_KEY 0
# define S_KEY 1
# define D_KEY 2
# define DOWN_ARROW_KEY 125
# define UP_ARROW_KEY 126
# define SPACE_KEY 49
# define M_KEY 46
# define N_KEY 45
# define MOUSE_LEFT 25 // nb: correspond to ( and )
# define MOUSE_RIGHT 29

# define NO 0
# define SO 1
# define EA 2
# define WE 3
# define F 4
# define C 5
# define D 6

// Colors
# define WHITE 16777215 //White
//# define RED 16711680 //Red
//# define GREEN 65280 //Green
//# define BLUE 255 //Blue

// Window size
//# define WIN_NX 1280 //values for macbook pro full screen
//# define WIN_NY 750

# define WIN_NX 1920 //values for home AOC screen
# define WIN_NY 1030

//# define WIN_NX 2560 //values for 42 mac
//# define WIN_NY 1395

// View parameters (cf https://permadi.com/1996/05/ray-casting-tutorial-4/)
# define PIX_PER_BLOCK 64 // Pixels per map blocks
# define FOV 1.0472f //60 degrees in rad
# define N_RAY 320
# define TEXT_SIZE 64 // texture are 64 x 64 pixels

// 3D image size
# define INTERP_FACT 4
# define IM3_NX 1280 //(N_RAY * INTERP_FACT)
# define IM3_NY 800  //(200 * INTERP_FACT)

// Dist from player to proj plane (from FOV and IM3_NX)
# define D_P2P 1108 //(277*INTERP_FACT) 

/********************* Structures *********************************************/

// int point 2D
typedef struct s_ipt2
{
	int	x;
	int	y;
}				t_ipt2;

// float point 2D
typedef struct s_fpt2
{
	float	x;
	float	y;
}				t_fpt2;

// int matrix (size m, n)
typedef struct s_imat
{
	int	m;
	int	n;
	int	*imat;
}				t_imat;

// Pointers to display session and window
/*
win holds the main 3D scene
win2 the optional 2d scene
*/
typedef struct s_xptr
{
	void	*mlx;
	void	*win;
	void	*win2;
}				t_xptr;

// Mlx_image info
typedef struct s_image
{
	void	*id;
	char	*addr;
	int		bpp;
	int		line_size;
	int		endian;
	int		nx;
	int		ny;
	int		pos_x;
	int		pos_y;
}				t_image;

// Player attributes
typedef struct s_player
{
	int		x;
	int		y;
	int		step;
	float	theta;
	float	d_theta;
	float	d_theta_mouse;
}				t_player;

// Data collected during parsing
typedef struct s_input
{
	//int		rgb_floor[3];
	//int		rgb_ceil[3];
	int		ceiling;
	int		floor;
	t_image	*textures;
	// char	**map;
	char	*map;
	int		m;
	int		n;
	int		p_i;
	int		p_j;
	char	p_dir;
	int		*text[5];
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	char	*no_path;
	char	*f_color;
	char	*c_color;
	char	*door_path;
}			t_input;

// Variables used in raycasting
typedef struct s_raycast
{
	t_fpt2	h_wall;
	t_fpt2	v_wall;
	float	h_dist;
	float	v_dist;
	int		is_h_door;
	int		is_v_door;
	t_ipt2	p0;
	t_ipt2	p1;
	float	theta_ray;
	float	wall_dist;
	int		*ptr_text;
	int		i;
}			t_raycast;

// For texture mapping when drawing columns
typedef struct s_text_map
{
	double	text_offset;
	double	dtext;
	int		*ptr_text;	
}			t_text_map;

typedef struct s_text
{
	void		*img;
	char		*addr;
	int			bpp;
	int			llen;
	int			endian;
	int			w;
	int			h;
}				t_text;

// Meta-struct of all other structs
typedef struct s_meta
{
	t_input		input;
	t_xptr		xp;
	t_image		im;
	t_image		im2;
	// t_text		*textures;
	// int			ceiling;
	// int			floor;
	int			flag_minimap;
	int			flag_mouse_on;
	t_imat		map2d;
	t_player	play;
	char		keys_down[256];
}				t_meta;

// Variables for Bresenham's segment tracing algo
// (only used in optional 2D scene)
typedef struct s_draw
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	error;
}				t_draw;

/********************* Functions *********************************************/

// Main
void	create_image(t_meta *meta);
void	create_2d_image(t_meta *meta); // only if SHOW_RAYS = 1

// Parsing
void	parse_input_file(char *f_name, t_input *input, t_meta *meta);

// parse.c
int		parse_map(char *in_file, t_meta *meta);
int		load_textures(t_meta *meta);

// Update and render
int		update_and_render(t_meta *meta);
void	render(t_meta *meta);

// Raycast
void	compute_rays(t_input *inp, t_player *play, t_meta *meta);

// Draw 2D scene (only if SHOW_RAYS = 1)
void	create_map2d(t_imat *map2d, t_input *input, t_meta *meta);
void	mat2im(t_imat *mat, t_image *im);
void	draw_player_im(t_player *play, t_image *im);

// Draw segment (only used in 2D scene)
void	draw_line_image(t_ipt2 *p0, t_ipt2 *p1, t_image *im, int color);

// Draw 3D scene
void	draw_column(int i_ray, float wall_dist, int *ptr_text, t_meta *meta);

// Hooks
void	init_hooks(t_meta *meta);
int		key_down_hook(int keycode, t_meta *meta);
int		key_up_hook(int keycode, t_meta *meta);
int		destroy_hook(t_meta *meta);
int		mouse_hook(int x,int y, t_meta *meta);

// Doors
void	try_switch_door(t_meta *meta);

// Minimap
void	draw_minimap(t_meta *meta);

// Utils
void	init_player_and_keys(t_player *play, t_input *input, char *keys_down);
void	init_mem_ptrs(t_meta *meta);
void	free_and_exit(char *msg, t_meta *meta);
//void	draw_box_around_image(t_image *im);

#endif
