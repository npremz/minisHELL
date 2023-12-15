/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 23:17:36 by lethomas          #+#    #+#             */
/*   Updated: 2023/12/15 01:05:36 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing_exec.h"

static void	ft_init_set_cmd(t_bool *is_cmd_name_yet_set, t_list **cmd_in,
	t_list **cmd_out, t_list **cmd_option)
{
	*is_cmd_name_yet_set = false;
	*cmd_in = NULL;
	*cmd_out = NULL;
	*cmd_option = NULL;
}

static int	ft_set_cmd_name(t_list *token_list, t_cmd *cmd,
	t_bool *is_cmd_name_yet_set)
{
	if (((t_token *)token_list->content)->type == word)
	{
		cmd->type = classic_cmd;
		*is_cmd_name_yet_set = true;
	}
	else if (((t_token *)token_list->content)->type == assignation)
		cmd->type = assignation_cmd;
	cmd->name = ft_strdup(((t_token *)token_list->content)->value);
	if (cmd->name == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	ft_set_arg_list(t_list *token_list, t_list **cmd_option)
{
	char	*option_value;
	t_list	*elem_option_list;

	option_value = ft_strdup(((t_token *)token_list->content)->value);
	if (option_value == NULL)
		return (EXIT_FAILURE);
	elem_option_list = ft_lstnew(option_value);
	if (elem_option_list == NULL)
		return (EXIT_FAILURE);
	ft_lstadd_back(cmd_option, elem_option_list);
	return (EXIT_SUCCESS);
}

static int	ft_set_cmd_name_option(t_list *token_list, t_cmd *cmd,
	t_list **cmd_option, t_bool *is_cmd_name_yet_set)
{
	if (*is_cmd_name_yet_set == false)
	{
		if (ft_set_cmd_name(token_list, cmd, is_cmd_name_yet_set))
			return (EXIT_FAILURE);
	}
	else
		ft_set_arg_list(token_list, cmd_option);
	return (EXIT_SUCCESS);
}

int	ft_set_cmd(t_list *token_list, int cmd_nb_token, t_cmd *cmd)
{
	t_bool	is_cmd_name_yet_set;
	t_list	*cmd_in;
	t_list	*cmd_out;
	t_list	*cmd_option;

	ft_init_set_cmd(&is_cmd_name_yet_set, &cmd_in, &cmd_out, &cmd_option);
	while (cmd_nb_token--)
	{
		if (ft_token_is_redirection_op((t_token *)token_list->content))
		{
			if (ft_set_cmd_redirection(&token_list, cmd, &cmd_in, &cmd_out))
				return (EXIT_FAILURE);
			cmd_nb_token--;
		}
		else
			if (ft_set_cmd_name_option(token_list, cmd, &cmd_option,
					&is_cmd_name_yet_set))
				return (EXIT_FAILURE);
		token_list = token_list->next;
	}
	if (ft_set_cmd_in_out_arg(cmd, cmd_in, cmd_out, cmd_option))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
