/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_search_item.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 17:57:05 by lethomas          #+#    #+#             */
/*   Updated: 2023/12/13 01:39:50 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	*ft_btree_search_item(t_btree *root, void *data_ref,
			int (*cmpf)(void *, void *))
{
	void	*elem_item;

	if (!root)
		return (NULL);
	if (root->left)
	{
		elem_item = ft_btree_search_item(root->left, data_ref, cmpf);
		if (elem_item)
			return (elem_item);
	}
	if (!(*cmpf)(data_ref, root->item))
		return (root->item);
	if (root->right)
	{
		elem_item = ft_btree_search_item(root->right, data_ref, cmpf);
		if (elem_item)
			return (elem_item);
	}
	return (NULL);
}
