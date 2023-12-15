/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_insert_data.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 11:44:09 by lethomas          #+#    #+#             */
/*   Updated: 2023/12/13 01:41:34 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static int	ft_btree_move_to_leaf(t_btree **moving_node,
	t_btree **moving_prev_node, t_btree **new_node, int (*cmpf)(void *, void *))
{
	int	right_left;

	if ((*cmpf)((*new_node)->item, (*moving_node)->item) >= 0)
	{
		right_left = 0;
		*moving_prev_node = *moving_node;
		*moving_node = (*moving_node)->right;
	}
	else
	{
		right_left = 1;
		*moving_prev_node = *moving_node;
		*moving_node = (*moving_node)->left;
	}
	return (right_left);
}

void	ft_btree_insert_data(t_btree **root, void *item,
			int (*cmpf)(void *, void *))
{
	t_btree	*new_node;
	t_btree	*moving_node;
	t_btree	*moving_prev_node;
	int		right_left;

	new_node = ft_btree_create_node (item);
	if (new_node == NULL)
		return ;
	if (!(*root))
	{
		*root = new_node;
		return ;
	}
	moving_node = *root;
	if (new_node)
	{
		while (moving_node)
			right_left = ft_btree_move_to_leaf(&moving_node, &moving_prev_node,
					&new_node, cmpf);
		if (right_left)
			moving_prev_node->left = new_node;
		else
			moving_prev_node->right = new_node;
	}
}
