/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_wildcard_for_cmd_list.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 19:36:12 by lethomas          #+#    #+#             */
/*   Updated: 2023/12/19 21:09:00 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing_exec.h"

static int	ft_update_cmd_redirection(char **cmd_red_name,
	t_list *new_red, int pos_to_insert)
{
	if (ft_lstsize(new_red) == 1)
	{
		free(cmd_red_name[pos_to_insert]);
		cmd_red_name[pos_to_insert] = (char *)new_red->content;
		free(new_red);
	}
	else
	{
		cmd_red_name[pos_to_insert]
			= ft_strjoin(cmd_red_name[pos_to_insert],
				":ambiguous_redirect", true, false);
		if (cmd_red_name[pos_to_insert] == NULL)
			return (EXIT_FAILURE);
		ft_lstclear(&new_red, &free);
	}
	return (EXIT_SUCCESS);
}

static int	ft_set_wildcard_for_cmd_redirection(char *red_name,
	char **cmd_red_name, t_list **cmd_red_wild)
{
	t_list	*new_red;
	t_list	*wildcard_bool_list_temp;
	int		pos_to_insert;

	pos_to_insert = 0;
	wildcard_bool_list_temp = (*cmd_red_wild)->prev;
	while (cmd_red_name[pos_to_insert] != red_name)
		pos_to_insert++;
	if (ft_get_wildcard_value(red_name, cmd_red_wild, &new_red))
		return (EXIT_FAILURE);
	if (new_red != NULL)
		if (ft_update_cmd_redirection(cmd_red_name,
				new_red, pos_to_insert))
			return (EXIT_FAILURE);
	if (ft_update_wildcard_bool_list_new_entry(*cmd_red_wild,
			cmd_red_name[pos_to_insert], &wildcard_bool_list_temp))
		return (EXIT_FAILURE);
	if (*cmd_red_wild == NULL)
		*cmd_red_wild = wildcard_bool_list_temp;
	if (*cmd_red_wild != NULL)
		while ((*cmd_red_wild)->prev != NULL)
			*cmd_red_wild = (*cmd_red_wild)->prev;
	return (EXIT_SUCCESS);
}

static t_bool	ft_has_a_wildcard(char **name, t_list **wildcard_list,
	char **wildcard_path)
{
	int		i;
	int		j;
	t_list	*new_wildcard_list;

	i = -1;
	if (name == NULL)
		return (false);
	while (name[++i] != NULL)
	{
		j = 0;
		new_wildcard_list = *wildcard_list;
		*wildcard_path = name[i];
		while (true)
		{
			while (name[i][j] != '*' && name[i][j] != '\0')
				j++;
			if (name[i][j] == '\0')
				break ;
			if (*((t_bool *)(*wildcard_list)->content) == true)
				return (*wildcard_list = new_wildcard_list, true);
			*wildcard_list = (*wildcard_list)->next;
			j++;
		}
	}
	return (false);
}

static int	ft_set_wildcard_for_cmd(t_cmd *cmd)
{
	char	*wild_name;

	while (ft_has_a_wildcard(cmd->in, &cmd->wildcard_in, &wild_name))
		if (ft_set_wildcard_for_cmd_redirection(wild_name, cmd->in,
				&cmd->wildcard_in))
			return (EXIT_FAILURE);
	while (ft_has_a_wildcard(cmd->out, &cmd->wildcard_out, &wild_name))
		if (ft_set_wildcard_for_cmd_redirection(wild_name, cmd->out,
				&cmd->wildcard_out))
			return (EXIT_FAILURE);
	while (ft_has_a_wildcard(cmd->arg + 1, &cmd->wildcard_arg, &wild_name))
		if (ft_set_wildcard_for_cmd_arg(wild_name, cmd))
			return (EXIT_FAILURE);
	while (ft_has_a_wildcard((char *[2]){cmd->name, NULL},
		&cmd->wildcard_name, &wild_name))
		if (ft_set_wildcard_for_cmd_name(cmd))
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_set_wildcard_for_cmd_list(t_list *cmd_list)
{
	while (cmd_list != NULL)
	{
		if (ft_set_wildcard_for_cmd((t_cmd *)(cmd_list->content)))
			return (EXIT_FAILURE);
		cmd_list = cmd_list->next;
	}
	return (EXIT_SUCCESS);
}
