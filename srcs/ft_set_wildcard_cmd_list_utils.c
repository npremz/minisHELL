/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_wildcard_cmd_list_utils.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 19:36:12 by lethomas          #+#    #+#             */
/*   Updated: 2023/12/17 01:51:02 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing_exec.h"

int	ft_set_wildcard_cmd_list_redirection_in(char *path, t_cmd *cmd,
	t_list **wildcard_cmd_list)
{
	t_list	*wildcard_value;
	int		pos_to_insert;
	t_cmd	*new_cmd;
	t_list	*new_elem;

	pos_to_insert = 0;
	wildcard_value = ft_get_wildcard_value(path, &cmd->wildcard_in);
	if (cmd->wildcard_in != NULL)
		while (cmd->wildcard_in->prev != NULL)
			cmd->wildcard_in = cmd->wildcard_in->prev;
	if (wildcard_value == NULL)
		return (EXIT_SUCCESS);
	while (cmd->in[pos_to_insert] != path)
		pos_to_insert++;
	while (wildcard_value != NULL)
	{
		if (ft_copy_cmd(cmd, &new_cmd))
			return (EXIT_FAILURE);
		free(new_cmd->in[pos_to_insert]);
		new_cmd->in[pos_to_insert] = (char *)wildcard_value->content;
		new_elem = ft_lstnew(new_cmd);
		if (new_elem == NULL)
			return (EXIT_FAILURE);
		ft_lstadd_back(wildcard_cmd_list, new_elem);
		wildcard_value = wildcard_value->next;
	}
	return (EXIT_SUCCESS);
}
//free la liste

int	ft_set_wildcard_cmd_list_redirection_out(char *path, t_cmd *cmd,
	t_list **wildcard_cmd_list)
{
	t_list	*wildcard_value;
	int		pos_to_insert;
	t_cmd	*new_cmd;
	t_list	*new_elem;

	pos_to_insert = 0;
	wildcard_value = ft_get_wildcard_value(path, &cmd->wildcard_out);
	if (cmd->wildcard_out != NULL)
		while (cmd->wildcard_out->prev != NULL)
			cmd->wildcard_out = cmd->wildcard_out->prev;
	if (wildcard_value == NULL)
		return (EXIT_SUCCESS);
	while (cmd->out[pos_to_insert] != path)
		pos_to_insert++;
	if (ft_copy_cmd(cmd, &new_cmd))
		return (EXIT_FAILURE);
	free(new_cmd->out[pos_to_insert]);
	if (ft_lstsize(wildcard_value) == 1)
		new_cmd->out[pos_to_insert] = (char *)wildcard_value->content;
	else
		new_cmd->out[pos_to_insert] = ft_strdup("error");
	if (new_cmd->out[pos_to_insert] == NULL)
		return (EXIT_FAILURE);
	new_elem = ft_lstnew(new_cmd);
	if (new_elem == NULL)
		return (EXIT_FAILURE);
	ft_lstadd_back(wildcard_cmd_list, new_elem);
	return (EXIT_SUCCESS);
}
//free la liste

int	ft_set_wildcard_cmd_list_arg(char *path, t_cmd *cmd,
	t_list **wildcard_cmd_list)
{
	t_list	*wildcard_value;
	int		pos_to_insert;
	t_cmd	*new_cmd;
	t_list	*new_elem;

	pos_to_insert = 1;
	wildcard_value = ft_get_wildcard_value(path, &cmd->wildcard_arg);
	if (cmd->wildcard_arg != NULL)
		while (cmd->wildcard_arg->prev != NULL)
			cmd->wildcard_arg = cmd->wildcard_arg->prev;
	if (wildcard_value == NULL)
		return (EXIT_SUCCESS);
	while (cmd->arg[pos_to_insert] != path)
		pos_to_insert++;
	while (wildcard_value != NULL)
	{
		if (ft_copy_cmd(cmd, &new_cmd))
			return (EXIT_FAILURE);
		free(new_cmd->arg[pos_to_insert]);
		new_cmd->arg[pos_to_insert] = (char *)wildcard_value->content;
		new_elem = ft_lstnew(new_cmd);
		if (new_elem == NULL)
			return (EXIT_FAILURE);
		ft_lstadd_back(wildcard_cmd_list, new_elem);
		wildcard_value = wildcard_value->next;
	}
	return (EXIT_SUCCESS);
}
//free la liste

int	ft_set_wildcard_cmd_list_name(char *path, t_cmd *cmd,
	t_list **wildcard_cmd_list)
{
	t_list	*wildcard_value;
	t_cmd	*new_cmd;
	t_list	*new_elem;

	wildcard_value = ft_get_wildcard_value(path, &cmd->wildcard_name);
	if (cmd->wildcard_name != NULL)
		while (cmd->wildcard_name->prev != NULL)
			cmd->wildcard_name = cmd->wildcard_name->prev;
	if (wildcard_value == NULL)
		return (EXIT_SUCCESS);
	while (wildcard_value != NULL)
	{
		if (ft_copy_cmd(cmd, &new_cmd))
			return (EXIT_FAILURE);
		free(new_cmd->name);
		new_cmd->name = (char *)wildcard_value->content;
		free(new_cmd->arg[0]);
		new_cmd->arg[0] = ft_strdup((char *)wildcard_value->content);
		new_elem = ft_lstnew(new_cmd);
		if (new_elem == NULL)
			return (EXIT_FAILURE);
		ft_lstadd_back(wildcard_cmd_list, new_elem);
		wildcard_value = wildcard_value->next;
	}
	return (EXIT_SUCCESS);
}
//avant de shift au debut verifier si le nom contient des wildcard, les mettre a zero
//free la liste
