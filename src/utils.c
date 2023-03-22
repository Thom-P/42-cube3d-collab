/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:57:04 by tplanes           #+#    #+#             */
/*   Updated: 2023/03/21 16:45:49 by tplanes          ###   ########.fr       */
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
	meta -> input.map = NULL;
	i = 0;
	while (i < 4)
		meta -> input.text[i++] = NULL;
	meta -> map2d.imat = NULL;
	return ;
}

static void	free_mem(t_meta *meta)
{
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
	free(meta -> map2d.imat);
	return ;
}

//nb: y axis pointing downward
void	init_player_and_keys(t_player *play, t_input *inp, char *keys_down)
{
	int	i;

	play -> x = inp -> p_j * PIX_PER_BLOCK;
	play -> y = inp -> p_i * PIX_PER_BLOCK;
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
	i = -1;
	while (++i < 256)
		keys_down[i] = 0;
	return ;
}
