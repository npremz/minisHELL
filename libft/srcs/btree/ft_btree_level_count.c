/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_level_count.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 17:57:05 by lethomas          #+#    #+#             */
/*   Updated: 2023/12/13 01:42:38 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static void	ft_btree_level_count_rec(t_btree *root, int *count, int *count_max)
{
	(*count)++;
	if (root->left)
		ft_btree_level_count_rec(root->left, count, count_max);
	if (root->right)
		ft_btree_level_count_rec(root->right, count, count_max);
	if (*count > *count_max)
		*count_max = *count;
	(*count)--;
}

int	ft_btree_level_count(t_btree *root)
{
	int	count;
	int	count_max;

	count = 0;
	count_max = 0;
	if (root)
		ft_btree_level_count_rec(root, &count, &count_max);
	return (count_max);
}
