/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 15:47:56 by lethomas          #+#    #+#             */
/*   Updated: 2023/11/27 19:26:38 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_elem;
	void	*new_content;
	t_list	*start_elem;

	if (!del || !f)
		return (NULL);
	start_elem = NULL;
	while (lst)
	{
		new_content = (*f)(lst->content);
		new_elem = ft_lstnew (new_content);
		if (!new_elem)
		{
			del (new_content);
			ft_lstclear (&start_elem, del);
			return (NULL);
		}
		ft_lstadd_back (&start_elem, new_elem);
		lst = lst->next;
	}
	return (start_elem);
}
