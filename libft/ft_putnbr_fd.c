/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42lausann>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:42:33 by tplanes           #+#    #+#             */
/*   Updated: 2022/10/24 14:05:54 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_recur_write(int n, int is_neg, int fd);

void	ft_putnbr_fd(int n, int fd)
{
	ft_recur_write(n, n < 0, fd);
	return ;
}

static void	ft_recur_write(int n, int is_neg, int fd)
{
	char	c;

	if (is_neg && n >= -9)
	{
		ft_putchar_fd('-', fd);
		ft_putchar_fd((char)(-n + '0'), fd);
		return ;
	}
	else if (!is_neg && n <= 9)
	{
		ft_putchar_fd((char)(n + '0'), fd);
		return ;
	}
	else
	{
		ft_recur_write(n / 10, is_neg, fd);
		c = (char)(-(is_neg * 2 - 1) * (n % 10) + '0');
		ft_putchar_fd(c, fd);
		return ;
	}
}
