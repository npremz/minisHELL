/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copy_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 20:24:23 by lethomas          #+#    #+#             */
/*   Updated: 2023/12/16 23:00:54 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing_exec.h"

static int	ft_tabcpy(char **tab_over, t_token_type *tab,
	t_token_type **new_tab)
{
	int		i;
	if (tab == NULL)
		return (EXIT_SUCCESS);
	i = 0;
	while (tab_over[i] != NULL)
		i++;
	*new_tab = (t_token_type *)malloc(i * sizeof(t_token_type));
	if (*new_tab == NULL)
		return (EXIT_FAILURE);
	i = 0;
	while (tab_over[i] != NULL)
	{
		(*new_tab)[i] = tab[i];
		i++;
	}
	return (EXIT_SUCCESS);
}

static int ft_strdup_tab(char **tab, char ***new_tab)
{
	int		i;
	char	*new_content;

	if (tab == NULL)
		return (EXIT_SUCCESS);
	i = 0;
	while (tab[i] != NULL)
		i++;
	*new_tab = (char **)malloc((i + 1) * sizeof(char *));
	if (*new_tab == NULL)
		return (EXIT_FAILURE);
	i = 0;
	while (tab[i] != NULL)
	{
		new_content = ft_strdup(tab[i]);
		if (new_content == NULL)
			return (EXIT_FAILURE);
		(*new_tab)[i] = new_content;
		i++;
	}
	(*new_tab)[i] = NULL;
	return (EXIT_SUCCESS);
}

static int	ft_lstcpy(t_list *list, t_list **new_list)
{
	t_list	*new_elem;
	int		*new_content;

	while (list != NULL)
	{
		new_content = (int *)malloc(sizeof(int));
		if (new_content == NULL)
			return (EXIT_FAILURE);
		*new_content = *(int *)list->content;
		new_elem = ft_lstnew(new_content);
		if (new_elem == NULL)
			return (EXIT_FAILURE);
		ft_lstadd_back(new_list, new_elem);
		list = list->next;
	}
	return (EXIT_SUCCESS);
}

static int	ft_copy_cmd_sub(t_cmd *cop_cmd, t_cmd *cmd)
{
	cop_cmd->name = ft_strdup(cmd->name);
	if (cop_cmd->name == NULL && cmd->name != NULL)
		return (EXIT_FAILURE);
	if (ft_lstcpy(cmd->wildcard_name, &cop_cmd->wildcard_name))
		return (EXIT_FAILURE);
	if (ft_strdup_tab(cmd->arg, &cop_cmd->arg))
		return (EXIT_FAILURE);
	if (ft_lstcpy(cmd->wildcard_arg, &cop_cmd->wildcard_arg))
		return (EXIT_FAILURE);
	if (ft_strdup_tab(cmd->in, &cop_cmd->in))
		return (EXIT_FAILURE);
	if (ft_lstcpy(cmd->wildcard_in, &cop_cmd->wildcard_in))
		return (EXIT_FAILURE);
	if (ft_tabcpy(cmd->in, cmd->type_in, &cop_cmd->type_in))
		return (EXIT_FAILURE);
	if (ft_strdup_tab(cmd->out, &cop_cmd->out))
		return (EXIT_FAILURE);
	if (ft_lstcpy(cmd->wildcard_out, &cop_cmd->wildcard_out))
		return (EXIT_FAILURE);
	if (ft_tabcpy(cmd->out, cmd->type_out, &cop_cmd->type_out))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_copy_cmd(t_cmd *cmd, t_cmd **cop_cmd)
{
	*cop_cmd = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	if (*cop_cmd == NULL)
		return (EXIT_FAILURE);
	(*cop_cmd)->type = cmd->type;
	if (ft_copy_cmd_sub(*cop_cmd, cmd))
		return (EXIT_FAILURE);
	(*cop_cmd)->root = cmd->root;
	return (EXIT_SUCCESS);
}
