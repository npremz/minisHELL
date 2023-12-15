/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_create_node.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 00:07:36 by lethomas          #+#    #+#             */
/*   Updated: 2023/12/13 01:39:15 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

t_btree	*ft_btree_create_node(void *item)
{
	t_btree	*new_node;

	new_node = (t_btree *)malloc(sizeof(t_btree));
	if (new_node == NULL)
		return (NULL);
	if (new_node)
	{
		new_node->left = NULL;
		new_node->right = NULL;
		new_node->item = item;
	}
	return (new_node);
}
