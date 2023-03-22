/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42lausann>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:27:56 by tplanes           #+#    #+#             */
/*   Updated: 2022/11/09 14:28:08 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		_init_buff(char **p_buff, int fd);

void	_free_set_null(char **p_buff);

char	*_fetch_line(char **p_buff, int i, int fd);

int		_parse_cat(char **line, char **p_buff, int i, int *j);

char	*get_next_line(int fd)
{
	static char	*buff_arr[N_FD_MAX];
	char		*line;
	int			i_buff;

	if (fd < 0 || fd >= N_FD_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	if (_init_buff(&buff_arr[fd], fd))
		return (NULL);
	i_buff = 0;
	while (buff_arr[fd][i_buff] == -1)
		i_buff++;
	line = _fetch_line(&buff_arr[fd], i_buff, fd);
	return (line);
}

// Keep reading file until new line found
char	*_fetch_line(char **p_buff, int i_buff, int fd)
{
	char		*line;
	ssize_t		n_by_rd;
	int			is_line_found;
	int			line_len;

	line = NULL;
	line_len = 0;
	while (1)
	{
		is_line_found = _parse_cat(&line, p_buff, i_buff, &line_len);
		if (is_line_found)
			return (line);
		n_by_rd = read(fd, *p_buff, BUFFER_SIZE);
		if (n_by_rd <= 0)
			break ;
		(*p_buff)[n_by_rd] = '\0';
		i_buff = 0;
	}
	_free_set_null(p_buff);
	if (n_by_rd == -1)
		_free_set_null(&line);
	return (line);
}

// Parse buffer until \n or end of buffer and returns an extended line
int	_parse_cat(char **line, char **p_buff, int i_buff, int *line_len)
{	
	char	*buff;
	int		k;

	buff = *p_buff;
	k = 0;
	while (buff[i_buff + k] != 0 && buff[i_buff + k] != '\n')
		k++;
	if (buff[i_buff + k] == '\n')
		k++;
	*line = extendn_copy(*line, line_len, &buff[i_buff], k);
	if (*line == NULL)
	{	
		_free_set_null(p_buff);
		return (1);
	}
	i_buff += k;
	if ((*line)[*line_len - 1] == '\n' ||
			(buff[i_buff] == 0 && i_buff < BUFFER_SIZE))
	{
		if ((*line)[*line_len - 1] != '\n' || buff[i_buff] == 0)
			_free_set_null(p_buff);
		return (1);
	}
	return (0);
}

// Create buffer on heap on 1st fd call and reads BUFFER_SIZE bytes
int	_init_buff(char **p_buff, int fd)
{
	ssize_t	n_by_rd;

	if (*p_buff == NULL)
	{
		*p_buff = (char *)malloc(BUFFER_SIZE + 1);
		if (*p_buff == NULL)
			return (-1);
		n_by_rd = read(fd, *p_buff, BUFFER_SIZE);
		if (n_by_rd <= 0)
		{
			_free_set_null(p_buff);
			return (-1);
		}
		(*p_buff)[n_by_rd] = '\0';
	}
	return (0);
}

void	_free_set_null(char **p_buff)
{
	free(*p_buff);
	*p_buff = NULL;
	return ;
}
