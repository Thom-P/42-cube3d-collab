/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42lausann>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:29:27 by tplanes           #+#    #+#             */
/*   Updated: 2022/11/13 13:01:01 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 500
# endif

# define N_FD_MAX 1024

//Project
char	*get_next_line(int fd);

// Utils
char	*extendn_copy(char *s, int *s_len, char *buff, int n);

#endif
