/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_cmd_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 08:24:21 by lethomas          #+#    #+#             */
/*   Updated: 2023/12/15 01:05:36 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing_exec.h"

static int	ft_get_cmd_nb_token(t_list *token_list)
{
	int	cmd_nb_token;

	cmd_nb_token = 0;
	while (token_list != NULL
		&& !ft_token_is_cmd_op((t_token *)token_list->content)
		&& ((t_token *)token_list->content)->type != left_parenthesis
		&& ((t_token *)token_list->content)->type != right_parenthesis)
	{
		cmd_nb_token++;
		token_list = token_list->next;
	}
	return (cmd_nb_token);
}

static t_cmd_type	ft_get_cmd_type(t_list *token_list, int *cmd_nb_token)
{
	*cmd_nb_token = 1;
	if (((t_token *)token_list->content)->type == left_parenthesis)
		return (left_parenthesis_cmd);
	else if (((t_token *)token_list->content)->type == right_parenthesis)
		return (right_parenthesis_cmd);
	else if (((t_token *)token_list->content)->type == pipe_operator)
		return (pipe_operator_cmd);
	else if (((t_token *)token_list->content)->type == and_operator)
		return (and_operator_cmd);
	else if (((t_token *)token_list->content)->type == or_operator)
		return (or_operator_cmd);
	else
		return (classic_cmd);
}

static int	ft_add_new_cmd(t_list **cmd_list, t_cmd *cmd)
{
	t_list	*elem_list_cmd;

	elem_list_cmd = ft_lstnew((void *)cmd);
	if (elem_list_cmd == NULL)
		return (EXIT_FAILURE);
	ft_lstadd_back(cmd_list, elem_list_cmd);
	return (EXIT_SUCCESS);
}

int	ft_create_cmd_list(t_list *token_list, t_list **cmd_list)
{
	int		cmd_nb_token;
	t_cmd	*cmd;
	t_list	*token_list_save;

	token_list_save = token_list;
	*cmd_list = NULL;
	while (token_list != NULL)
	{
		cmd = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
		if (cmd == NULL)
			return (EXIT_FAILURE);
		cmd->type = ft_get_cmd_type(token_list, &cmd_nb_token);
		if (cmd->type == classic_cmd)
		{
			cmd_nb_token = ft_get_cmd_nb_token(token_list);
			if (ft_set_cmd(token_list, cmd_nb_token, cmd))
				return (EXIT_FAILURE);
		}
		if (ft_add_new_cmd(cmd_list, cmd))
			return (EXIT_FAILURE);
		while (cmd_nb_token--)
			token_list = token_list->next;
	}
	ft_free_token_list(&token_list_save);
	return (EXIT_SUCCESS);
}
