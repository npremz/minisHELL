/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstshift.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 01:35:12 by lethomas          #+#    #+#             */
/*   Updated: 2024/03/09 11:31:30 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

t_list	*ft_lstshift(t_list *elem, int shift)
{
	if (shift > 0)
		while (elem != NULL && shift--)
			elem = elem->next;
	else if (shift < 0)
		while (elem != NULL && shift++)
			elem = elem->prev;
	return (elem);
}
