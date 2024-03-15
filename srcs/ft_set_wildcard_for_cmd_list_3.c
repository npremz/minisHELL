/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_wildcard_for_cmd_list_3.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 21:52:24 by lethomas          #+#    #+#             */
/*   Updated: 2024/03/15 11:47:35 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_insertion_sort(t_list *list)
{
	void	*temp_char;
	t_list	*temp_list;

	while (list != NULL)
	{
		temp_list = list;
		while (list->prev != NULL
			&& ft_strncmp((char *)list->content, (char *)list->prev->content,
				ft_strlen((char *)list->content) + 1) < 0)
		{
			temp_char = list->content;
			list->content = list->prev->content;
			list->prev->content = temp_char;
			list = list->prev;
		}
		list = temp_list->next;
	}
}

static int	ft_malloc_new_arg_tab(char **tab, t_list *new_args,
	char ***new_arg_tab)
{
	int	tab_size;

	tab_size = 0;
	while (tab[tab_size] != NULL)
		tab_size++;
	*new_arg_tab = (char **)malloc((tab_size + ft_lstsize(new_args))
			* sizeof(char *));
	if (*new_arg_tab == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	ft_update_cmd_arg(char *arg_name, t_cmd *cmd, t_list *new_args,
	t_list	**wildcard_bool_list_temp)
{
	char	**new_arg_tab;
	int		pos_to_insert;
	int		i;

	pos_to_insert = -1;
	i = -1;
	ft_insertion_sort(new_args);
	if (ft_malloc_new_arg_tab(cmd->arg, new_args, &new_arg_tab))
		return (EXIT_FAILURE);
	while (cmd->arg[++pos_to_insert] != arg_name)
		new_arg_tab[pos_to_insert] = cmd->arg[pos_to_insert];
	free(cmd->arg[pos_to_insert]);
	while (new_args != NULL)
	{
		new_arg_tab[pos_to_insert + ++i] = (char *)new_args->content;
		if (ft_update_wildcard_bool_list_new_entry(cmd->wildcard_arg,
				(char *)new_args->content, wildcard_bool_list_temp))
			return (EXIT_FAILURE);
		new_args = new_args->next;
	}
	while (cmd->arg[++pos_to_insert - 1] != NULL)
		new_arg_tab[pos_to_insert + i] = cmd->arg[pos_to_insert];
	free(cmd->arg);
	cmd->arg = new_arg_tab;
	return (EXIT_SUCCESS);
}

int	ft_set_wildcard_for_cmd_arg(char *arg_name, t_cmd *cmd)
{
	t_list	*new_args;
	t_list	*wildcard_bool_list_temp;

	wildcard_bool_list_temp = cmd->wildcard_arg->prev;
	if (ft_get_wildcard_value(arg_name, &cmd->wildcard_arg, &new_args))
		return (EXIT_FAILURE);
	if (new_args != NULL)
		if (ft_update_cmd_arg(arg_name, cmd, new_args,
				&wildcard_bool_list_temp))
			return (EXIT_FAILURE);
	if (new_args == NULL)
		if (ft_update_wildcard_bool_list_new_entry(cmd->wildcard_arg,
				arg_name, &wildcard_bool_list_temp))
			return (EXIT_FAILURE);
	if (cmd->wildcard_arg == NULL)
		cmd->wildcard_arg = wildcard_bool_list_temp;
	ft_lstclear(&new_args, NULL);
	if (cmd->wildcard_arg != NULL)
		while (cmd->wildcard_arg->prev != NULL)
			cmd->wildcard_arg = cmd->wildcard_arg->prev;
	return (EXIT_SUCCESS);
}
