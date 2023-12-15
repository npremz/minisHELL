/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 00:04:44 by lethomas          #+#    #+#             */
/*   Updated: 2023/12/13 01:40:30 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BTREE_H
# define BTREE_H

t_btree	*ft_btree_create_node(void *item);
void	ft_btree_apply_infix(t_btree *root, void (*applyf)(void *));
void	ft_btree_apply_prefix(t_btree *root, void (*applyf)(void *));
void	ft_btree_apply_suffix(t_btree *root, void (*applyf)(void *));
void	ft_btree_insert_data(t_btree **root, void *item,
			int (*cmpf)(void *, void *));
int		ft_btree_level_count(t_btree *root);
void	*ft_btree_search_item(t_btree *root, void *data_ref,
			int (*cmpf)(void *, void *));

#endif
