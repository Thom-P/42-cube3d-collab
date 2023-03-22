/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42lausann>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:46:19 by tplanes           #+#    #+#             */
/*   Updated: 2022/10/20 15:57:56 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lst_out;
	t_list	*new;
	void	*ptr_content;

	lst_out = NULL;
	while (lst)
	{
		ptr_content = f(lst -> content);
		new = ft_lstnew(ptr_content);
		if (new == NULL)
		{
			del(ptr_content);
			ft_lstclear(&lst_out, del);
			return (NULL);
		}
		ft_lstadd_back(&lst_out, new);
		lst = lst -> next;
	}
	return (lst_out);
}
