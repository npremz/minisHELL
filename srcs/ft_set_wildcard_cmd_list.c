/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_wildcard_cmd_list.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 22:33:22 by lethomas          #+#    #+#             */
/*   Updated: 2023/12/16 23:37:15 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing_exec.h"

static t_bool	ft_set_info(t_list *new_wildcard_list,
	t_list **wildcard_list, t_bool *has_set)
{
	*has_set = true;
	*wildcard_list = new_wildcard_list;
	return (true);
}

static t_bool	ft_has_a_wildcard(char **name, t_list **wildcard_list,
	char **wildcard_path, t_bool *has_set)
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
				return (ft_set_info(new_wildcard_list, wildcard_list, has_set));
			*wildcard_list = (*wildcard_list)->next;
			j++;
		}
	}
	return (false);
}

int	ft_set_wildcard_cmd_list(t_cmd *cmd, t_list **wildcard_cmd,
	t_bool *has_set)
{
	char	*path;

	*wildcard_cmd = NULL;
	*has_set = false;
	if (ft_has_a_wildcard(cmd->in, &cmd->wildcard_in, &path, has_set))
	{
		if (ft_set_wildcard_cmd_list_redirection_in(path, cmd, wildcard_cmd))
			return (EXIT_FAILURE);
	}
	else if (ft_has_a_wildcard(cmd->out, &cmd->wildcard_out, &path, has_set))
	{
		if (ft_set_wildcard_cmd_list_redirection_out(path, cmd, wildcard_cmd))
			return (EXIT_FAILURE);
	}
	else if (ft_has_a_wildcard(cmd->arg + 1, &cmd->wildcard_arg, &path, has_set))
	{
		if (ft_set_wildcard_cmd_list_arg(path, cmd, wildcard_cmd))
			return (EXIT_FAILURE);
	}
	else if (ft_has_a_wildcard((char *[2]){cmd->name, NULL},
		&cmd->wildcard_name, &path, has_set))
		if (ft_set_wildcard_cmd_list_name(path, cmd, wildcard_cmd))
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
