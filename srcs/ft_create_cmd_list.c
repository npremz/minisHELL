/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_cmd_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 08:24:21 by lethomas          #+#    #+#             */
/*   Updated: 2023/12/12 18:39:26 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

static int	ft_get_cmd_nb_token(t_list *token_list)
{
	int	cmd_nb_token;

	cmd_nb_token = 0;
	while (token_list != NULL
		&& ((t_token *)token_list->content)->type != pipe_operator
		&& ((t_token *)token_list->content)->type != and_operator
		&& ((t_token *)token_list->content)->type != or_operator
		&& ((t_token *)token_list->content)->type != left_parenthesis
		&& ((t_token *)token_list->content)->type != right_parenthesis)

	{
		cmd_nb_token++;
		token_list = token_list->next;
	}
	return (cmd_nb_token);
}

static int	ft_set_cmd(t_list *token_list, int cmd_nb_token,
	t_cmd *cmd)
{
	t_bool	is_cmd_name_yet_set;
	t_list	*cmd_option;
	t_list	*cmd_option_temp;
	t_list	*elem_option_list;
	char	*option_value;
	int		i;

	is_cmd_name_yet_set = false;
	cmd_option = NULL;
	while (cmd_nb_token--)
	{
		if (((t_token *)token_list->content)->type == redirection_in
			|| ((t_token *)token_list->content)->type == redirection_out
			|| ((t_token *)token_list->content)->type == redirection_append
			|| ((t_token *)token_list->content)->type == redirection_here_doc)
		{
			if (((t_token *)token_list->content)->type == redirection_here_doc
				|| ((t_token *)token_list->content)->type == redirection_in)
			{
				cmd->type_in = ((t_token *)token_list->content)->type;
				cmd->in = ft_strdup(((t_token *)token_list->next->content)->value);
			}
			else
			{
				cmd->type_out = ((t_token *)token_list->content)->type;
				cmd->out = ft_strdup(((t_token *)token_list->next->content)->value);
			}
			token_list = token_list->next;
			cmd_nb_token--;
		}
		else if (is_cmd_name_yet_set == false)
		{
			is_cmd_name_yet_set = true;
			cmd->name
				= ft_strdup(((t_token *)token_list->content)->value);
			if (cmd->name == NULL)
				return (EXIT_FAILURE);
		}
		else
		{
			option_value
				= ft_strdup(((t_token *)token_list->content)->value);
			if (option_value == NULL)
				return (EXIT_FAILURE);
			elem_option_list = ft_lstnew(option_value);
			if (elem_option_list == NULL)
				return (EXIT_FAILURE);
			ft_lstadd_back(&cmd_option, elem_option_list);
		}
		token_list = token_list->next;
	}
	cmd->arg = (char **)malloc(sizeof(char *) * (1 + ft_lstsize(cmd_option)));
	cmd->arg[0] = cmd->name;
	i = 1;
	while (cmd_option != NULL)
	{
		cmd->arg[i++] = (char *)cmd_option->content;
		cmd_option_temp = cmd_option->next;
		free(cmd_option);
		cmd_option = cmd_option_temp;
	}
	return (EXIT_SUCCESS);
}

int	ft_create_cmd_list(t_list *token_list, t_list **cmd_list)
{
	int		cmd_nb_token;
	t_cmd	*cmd;
	t_list	*token_list_save;
	t_list	*elem_list_cmd;

	token_list_save = token_list;
	*cmd_list = NULL;
	while (token_list != NULL)
	{
		cmd = (t_cmd *)calloc(1, sizeof(t_cmd));
		if (cmd == NULL)
			return (EXIT_FAILURE);
		cmd_nb_token = 1; //a deux selon l op !!
		if (((t_token *)token_list->content)->type == left_parenthesis)
			cmd->type = left_parenthesis_cmd;
		else if (((t_token *)token_list->content)->type == right_parenthesis)
			cmd->type = right_parenthesis_cmd;
		else if (((t_token *)token_list->content)->type == pipe_operator)
			cmd->type = pipe_operator_cmd;
		else if (((t_token *)token_list->content)->type == and_operator)
			cmd->type = and_operator_cmd;
		else if (((t_token *)token_list->content)->type == or_operator)
			cmd->type = or_operator_cmd;
		else
		{
			cmd->type = classic_cmd;
			cmd_nb_token = ft_get_cmd_nb_token(token_list);
			if (ft_set_cmd(token_list, cmd_nb_token, cmd))
				return (EXIT_FAILURE);
		}
		elem_list_cmd = ft_lstnew((void *)cmd);
		if (elem_list_cmd == NULL)
			return (EXIT_FAILURE);
		ft_lstadd_back(cmd_list, elem_list_cmd);
		while (cmd_nb_token--)
			token_list = token_list->next;
	}
	ft_free_token_list(&token_list_save);
	return (EXIT_SUCCESS);
}
