/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 15:47:36 by lethomas          #+#    #+#             */
/*   Updated: 2023/12/19 21:01:42 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*elem_temp;

	if (lst == NULL)
		return ;
	while (*lst != NULL)
	{
		elem_temp = (*lst)->next;
		ft_lstdelone (*lst, del);
		*lst = elem_temp;
	}
}
