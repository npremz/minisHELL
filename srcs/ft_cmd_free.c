/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 16:05:48 by lethomas          #+#    #+#             */
/*   Updated: 2024/03/07 14:13:17 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab == NULL)
		return ;
	while (tab[i] != NULL)
		free(tab[i++]);
	free(tab);
}

void	ft_free_cmd(void *cmd)
{
	if (cmd == NULL)
		return ;
	free(((t_cmd *)cmd)->name);
	free(((t_cmd *)cmd)->type_in);
	free(((t_cmd *)cmd)->type_out);
	ft_free_tab(((t_cmd *)cmd)->arg);
	ft_free_tab(((t_cmd *)cmd)->in);
	ft_free_tab(((t_cmd *)cmd)->out);
	ft_lstclear(&((t_cmd *)cmd)->wildcard_name, &free);
	ft_lstclear(&((t_cmd *)cmd)->wildcard_arg, &free);
	ft_lstclear(&((t_cmd *)cmd)->wildcard_in, &free);
	ft_lstclear(&((t_cmd *)cmd)->wildcard_out, &free);
	free(cmd);
}

void	ft_free_cmd_list(t_list *cmd_list)
{
	t_list	*cmd_list_temp;

	while (cmd_list != NULL)
	{
		cmd_list_temp = cmd_list->next;
		if (((t_cmd *)cmd_list->content)->type == left_parenthesis_cmd
			|| ((t_cmd *)cmd_list->content)->type == right_parenthesis_cmd)
			ft_free_cmd(cmd_list->content);
		free(cmd_list);
		cmd_list = cmd_list_temp;
	}
}

static void	ft_btree_free(t_btree *cmd_tree)
{
	if (cmd_tree == NULL)
		return ;
	if (cmd_tree->left)
		ft_btree_free(cmd_tree->left);
	if (cmd_tree->right)
		ft_btree_free(cmd_tree->right);
	free(cmd_tree);
}

void	ft_free_cmd_tree(t_btree *cmd_tree)
{
	ft_btree_apply_suffix(cmd_tree, &ft_free_cmd);
	ft_btree_free(cmd_tree);
}
