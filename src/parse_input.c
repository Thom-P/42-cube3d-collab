/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 15:30:54 by tplanes           #+#    #+#             */
/*   Updated: 2023/03/22 14:47:08 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "main.h"

//Just a dummy parsing, hardcoded map at the moment
void	parse_input_file(char *file_in, t_input *input, t_meta *meta)
{
	(void) file_in;
	char	**map;

	input -> m = 15;
	input -> n = 10;
	char  tmp[15][10] = {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
						 {1, 0, 1, 1, 0, 0, 1, 0, 0, 1},
						 {1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
						 {1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
						 {1, 0, 0, 0, 0, 0, 0, 0, 1, 1},
						 {1, 0, 0, 0, 0, 0, 0, 1, 1, 1},
						 {1, 0, 0, 0, 0, 0, 0, 0, 1, 1},
						 {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
						 {1, 0, 0, 0, 0, 0, 0, 1, 2, 1},
						 {1, 0, 0, 1, 1, 0, 0, 1, 0, 1},
						 {1, 2, 1, 1, 1, 0, 0, 1, 0, 1},
						 {1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
						 {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
						 {1, 0, 0, 1, 1, 0, 0, 0, 0, 1},
					 	 {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
	
	input -> p_i = 3; // row index of player start
	input -> p_j = 5; // col index of player start
	input -> p_dir = 'N'; // orientation of player
	input -> rgb_floor[0] = 150; //RGB colors of floor and ceiling
	input -> rgb_floor[1] = 150;
	input -> rgb_floor[2] = 150;
	input -> rgb_ceil[0] = 255;
	input -> rgb_ceil[1] = 255;
	input -> rgb_ceil[2] = 0;

	// copy hardcoded map into malloced array
	map = (char **)malloc((size_t)input -> m * sizeof(char *));
	if (map == NULL)
		free_and_exit("In parsing", meta);
	int i = 0;
	int j = 0;
	while (i < input -> m)
	{
		map[i] = (char *)malloc((size_t)input -> n *sizeof(char));
		if (map[i] == NULL)
			free_and_exit("In parsing", meta);
		j = 0;
		while (j < input -> n)
		{	
			map[i][j] = tmp[i][j];
			j++;
		}
		i++;
	}
	input -> map = map;
	
	// Load textures in N, S, E, W order
	char	*file_text[5];
	file_text[0] = ft_strdup("./src/textures/textN");
	if (file_text[0] == NULL)
		free_and_exit("In parsing", meta);
	file_text[1] = ft_strdup("./src/textures/textS");
	if (file_text[1] == NULL)
		free_and_exit("In parsing", meta); //warning, missing some free here
	file_text[2] = ft_strdup("./src/textures/textE");
	if (file_text[2] == NULL)
		free_and_exit("In parsing", meta);
	file_text[3] = ft_strdup("./src/textures/textE");
	if (file_text[3] == NULL)
		free_and_exit("In parsing", meta);
	file_text[4] = ft_strdup("./src/textures/textW"); //doors
	if (file_text[4] == NULL)
		free_and_exit("In parsing", meta);


	int n_by_text = PIX_PER_BLOCK * PIX_PER_BLOCK *sizeof(int);
	int	n_by_rd;
	int	**text = input -> text;
	int k = 0;
	int fd;
	while (k < 5)
	{
		text[k] = (int *)malloc((size_t)n_by_text);
		if (text[k] == NULL)
			free_and_exit("In parsing", meta); // missing frees here
		fd = open(file_text[k], O_RDONLY);
		if (fd < 0)
			free_and_exit("In parsing", meta);
		n_by_rd = (int)read(fd, (void *)text[k], (size_t)n_by_text);
		close(fd);
		if (n_by_rd != n_by_text)
			free_and_exit("Parsed wrong number of bytes in texture", meta);
		k++;
	}
	return ;
}
