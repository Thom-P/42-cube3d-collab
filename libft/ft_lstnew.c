/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42lausann>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:43:35 by tplanes           #+#    #+#             */
/*   Updated: 2022/10/20 12:43:43 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*ptr_node;

	ptr_node = (t_list *)malloc(sizeof(t_list));
	if (ptr_node == NULL)
		return (NULL);
	ptr_node -> content = content;
	ptr_node -> next = NULL;
	return (ptr_node);
}
