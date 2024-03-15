/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_wildcard_for_cmd_list_2.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 20:38:04 by lethomas          #+#    #+#             */
/*   Updated: 2024/03/15 12:02:14 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_malloc_new_arg_tab(char **tab, t_list *new_args,
	char ***new_arg_tab)
{
	int	tab_size;

	tab_size = 0;
	while (tab[tab_size] != NULL)
		tab_size++;
	*new_arg_tab = (char **)malloc((tab_size + ft_lstsize(new_args) + 1)
			* sizeof(char *));
	if (*new_arg_tab == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	ft_update_cmd_arg(t_cmd *cmd, t_list *new_args)
{
	char	**new_arg_tab;
	int		i;
	int		i2;

	i = 1;
	i2 = 1;
	if (ft_malloc_new_arg_tab(cmd->arg, new_args, &new_arg_tab))
		return (EXIT_FAILURE);
	new_arg_tab[0] = cmd->arg[0];
	while (new_args != NULL)
	{
		new_arg_tab[i++] = (char *)new_args->content;
		new_args = new_args->next;
	}
	while (cmd->arg[i2] != NULL)
		new_arg_tab[i++] = cmd->arg[i2++];
	new_arg_tab[i] = NULL;
	free(cmd->arg);
	cmd->arg = new_arg_tab;
	return (EXIT_SUCCESS);
}

static int	ft_set_new_name(t_cmd *cmd, t_list *new_name)
{
	ft_insertion_sort(new_name);
	free(cmd->name);
	cmd->name = (char *)new_name->content;
	free(cmd->arg[0]);
	cmd->arg[0] = ft_strdup((char *)new_name->content);
	if (cmd->arg[0] == NULL)
		return (EXIT_FAILURE);
	if (new_name->next != NULL)
		if (ft_update_cmd_arg(cmd, new_name->next))
			return (EXIT_FAILURE);
	ft_lstclear(&new_name, NULL);
	return (EXIT_SUCCESS);
}

int	ft_set_wildcard_for_cmd_name(t_cmd *cmd)
{
	t_list	*new_name;
	t_list	*wildcard_bool_list_temp;

	wildcard_bool_list_temp = cmd->wildcard_name->prev;
	if (ft_get_wildcard_value(cmd->name, &cmd->wildcard_name, &new_name))
		return (EXIT_FAILURE);
	if (new_name != NULL)
		if (ft_set_new_name(cmd, new_name))
			return (EXIT_FAILURE);
	if (ft_update_wildcard_bool_list_new_entry(cmd->wildcard_name,
			cmd->name, &wildcard_bool_list_temp))
		return (EXIT_FAILURE);
	if (cmd->wildcard_name == NULL)
		cmd->wildcard_name = wildcard_bool_list_temp;
	if (cmd->wildcard_name != NULL)
		while (cmd->wildcard_name->prev != NULL)
			cmd->wildcard_name = cmd->wildcard_name->prev;
	return (EXIT_SUCCESS);
}
