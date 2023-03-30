/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:29:51 by saeby             #+#    #+#             */
/*   Updated: 2023/03/30 14:20:52 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	load_sprites(t_meta *meta)
{
	meta->input.textures[5].id = mlx_xpm_file_to_image(meta->xp.mlx, \ //free and exit if NULL
								BIRD_SPRITE, \
								&(meta->input.textures[5].nx), \
								&(meta->input.textures[5].ny));
}

void	get_sprite_addr(t_meta *meta)
{
	meta->input.textures[5].addr = (char *)mlx_get_data_addr(\
									meta->input.textures[5].id, \
									&meta->input.textures[5].bpp, \
									&meta->input.textures[5].line_size, \
									&meta->input.textures[5].endian);
}
