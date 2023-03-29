/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:57:04 by tplanes           #+#    #+#             */
/*   Updated: 2023/03/29 16:12:37 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	free_mem(t_meta *meta);

void	free_and_exit(char *msg, t_meta *meta)
{
	int	status;

	status = 0;
	if (msg)
	{
		perror(msg);
		status = 1;
	}
	free_mem(meta);
	exit(status);
}

// Set all pointers that will be malloced to NULL
// Also init flag_minimap off
void	init_mem_ptrs(t_meta *meta)
{
	int	i;

	meta -> flag_minimap = 0;
	meta -> flag_bird = 0;
	meta -> flag_mouse_on = 0;
	meta -> input.map = NULL;
	meta -> input.m = 0;
	meta -> input.n = 0;
	i = 0;
	while (i < 4)
		meta -> input.text[i++] = NULL;
	meta -> map2d.imat = NULL;
	meta -> input.textures = NULL;
	return ;
}

static void	free_mem(t_meta *meta)
{
	(void) meta;
	return ;
}
// to rework with new maps and textures
/*
int		i;
t_input	*inp;

i = 0;
inp = &meta -> input;
if (inp -> map != NULL)
{
	while (i < inp -> m)
		free(inp -> map[i++]);
	free(inp -> map);
}
i = 0;
while (i < 4)
	free(inp -> text[i++]);
free(meta -> map2d.imat);*/

//nb: y axis pointing downward
void	init_player_and_keys(t_player *play, t_input *inp, t_sprite *sp,
							char *keys_down)
{
	int	i;

	play -> x = inp -> p_j * PIX_PER_BLOCK + PIX_PER_BLOCK / 2;
	play -> y = inp -> p_i * PIX_PER_BLOCK + PIX_PER_BLOCK / 2;
	sp -> x = play -> x;
	sp -> y = play -> y;
	printf("%i %i\n", play->x, play->y);
	play -> step = 5;
	if (inp -> p_dir == 'E')
		play -> theta = 0;
	else if (inp -> p_dir == 'N')
		play -> theta = 3 * PI / 2;
	else if (inp -> p_dir == 'W')
		play -> theta = PI;
	else if (inp -> p_dir == 'S')
		play -> theta = PI / 2;
	play -> d_theta = PI / 100;
	play -> d_theta_mouse = PI / 1000;
	i = -1;
	while (++i < 256)
		keys_down[i] = 0;
	return ;
}
