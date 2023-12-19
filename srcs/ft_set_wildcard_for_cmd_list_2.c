/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_wildcard_for_cmd_list_2.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 20:38:04 by lethomas          #+#    #+#             */
/*   Updated: 2023/12/19 00:10:36 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing_exec.h"

static void	ft_set_front_first_elem_alpha_order(t_list *list)
{
	void	*content_temp;

	while (list->next != NULL)
		list = list->next;
	while (list->prev != NULL)
	{
		if (ft_strncmp((char *)list->content, (char *)list->prev->content,
				ft_strlen((char *)list->content) + 1) < 0)
		{
			content_temp = list->content;
			list->content = list->prev->content;
			list->prev->content = content_temp;
		}
		list = list->prev;
	}
}

int	ft_set_wildcard_for_cmd_name(t_cmd *cmd)
{
	t_list	*new_name;

	new_name = ft_get_wildcard_value(cmd->name, &cmd->wildcard_name);
	if (new_name != NULL)
	{
		ft_set_front_first_elem_alpha_order(new_name);
		free(cmd->name);
		cmd->name = (char *)new_name->content;
		free(cmd->arg[0]);
		cmd->arg[0] = ft_strdup((char *)new_name->content);
		if (cmd->arg[0] == NULL)
			return (EXIT_FAILURE);
		ft_lstclear(&new_name->next, &free);
		free(new_name);
		if (ft_update_wildcard_bool_list_new_entry(&cmd->wildcard_name,
				cmd->name, false))
			return (EXIT_FAILURE);
	}
	if (cmd->wildcard_name != NULL)
		while (cmd->wildcard_name->prev != NULL)
			cmd->wildcard_name = cmd->wildcard_name->prev;
	return (EXIT_SUCCESS);
}

static int	ft_tabsize(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
		i++;
	return (i);
}

static int	ft_update_cmd_arg(char *arg_name, t_cmd *cmd, t_list *new_args)
{
	char	**new_arg_tab;
	int		pos_to_insert;
	int		i;

	pos_to_insert = -1;
	i = -1;
	new_arg_tab = (char **)malloc((ft_tabsize(cmd->arg)
				+ ft_lstsize(new_args)) * sizeof(char *));
	if (new_arg_tab == NULL)
		return (EXIT_FAILURE);
	while (cmd->arg[++pos_to_insert] != arg_name)
		new_arg_tab[pos_to_insert] = cmd->arg[pos_to_insert];
	free(cmd->arg[pos_to_insert]);
	while (new_args != NULL)
	{
		new_arg_tab[pos_to_insert + ++i] = (char *)new_args->content;
		if (ft_update_wildcard_bool_list_new_entry(&cmd->wildcard_arg,
				(char *)new_args->content, i != 0))
			return (EXIT_FAILURE);
		new_args = new_args->next;
	}
	while (cmd->arg[++pos_to_insert - 1] != NULL)
		new_arg_tab[pos_to_insert + i] = cmd->arg[pos_to_insert];
	free(cmd->arg);
	cmd->arg = new_arg_tab;
	return (EXIT_SUCCESS);
}
//revoir i != 0  !!!!!!! false tant que rien n a ete ajopute

int	ft_set_wildcard_for_cmd_arg(char *arg_name, t_cmd *cmd)
{
	t_list	*new_args;
	t_list	*elem_temp;

	new_args = ft_get_wildcard_value(arg_name, &cmd->wildcard_arg);
	if (new_args != NULL)
		if (ft_update_cmd_arg(arg_name, cmd, new_args))
			return (EXIT_FAILURE);
	while (new_args != NULL)
	{
		elem_temp = new_args->next;
		free(new_args);
		new_args = elem_temp;
	}
	if (cmd->wildcard_arg != NULL)
		while (cmd->wildcard_arg->prev != NULL)
			cmd->wildcard_arg = cmd->wildcard_arg->prev;
	return (EXIT_SUCCESS);
}
