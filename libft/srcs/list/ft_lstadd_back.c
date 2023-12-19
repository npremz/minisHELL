/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 15:47:25 by lethomas          #+#    #+#             */
/*   Updated: 2023/12/18 22:24:42 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*elem_temp;

	if (lst == NULL || new == NULL)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		elem_temp = ft_lstlast(*lst);
		elem_temp->next = new;
		new->prev = elem_temp;
	}
}
