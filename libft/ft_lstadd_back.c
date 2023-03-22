/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42lausann>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:45:10 by tplanes           #+#    #+#             */
/*   Updated: 2022/10/20 12:45:16 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	if (*lst == NULL)
	{	
		*lst = new;
		return ;
	}
	while ((*lst)-> next)
		lst = &((*lst)-> next);
	(*lst)-> next = new;
	return ;
}
