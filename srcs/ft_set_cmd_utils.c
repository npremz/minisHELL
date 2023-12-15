/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_cmd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 23:44:56 by lethomas          #+#    #+#             */
/*   Updated: 2023/12/15 01:05:36 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing_exec.h"

static int	ft_set_cmd_redirection_list(t_list **token_list,
	t_token_type *redirection_type, t_list **list_cmd_redirection)
{
	t_list	*elem_redirection_list;
	char	*redirection_value;

	*redirection_type = ((t_token *)(*token_list)->content)->type;
	redirection_value
		= ft_strdup(((t_token *)(*token_list)->next->content)->value);
	if (redirection_value == NULL)
		return (EXIT_FAILURE);
	elem_redirection_list = ft_lstnew(redirection_value);
	if (elem_redirection_list == NULL)
		return (EXIT_FAILURE);
	ft_lstadd_back(list_cmd_redirection, elem_redirection_list);
	return (EXIT_SUCCESS);
}

int	ft_set_cmd_redirection(t_list **token_list, t_cmd *cmd,
	t_list **list_cmd_in, t_list **list_cmd_out)
{
	t_token_type	*redirection_type;
	t_list			**list_cmd_redirection;

	if (((t_token *)(*token_list)->content)->type == redirection_here_doc
		|| ((t_token *)(*token_list)->content)->type == redirection_in)
	{
		redirection_type = &cmd->type_in;
		list_cmd_redirection = list_cmd_in;
	}
	else
	{
		redirection_type = &cmd->type_out;
		list_cmd_redirection = list_cmd_out;
	}
	if (ft_set_cmd_redirection_list(token_list, redirection_type,
			list_cmd_redirection))
		return (EXIT_FAILURE);
	*token_list = (*token_list)->next;
	return (EXIT_SUCCESS);
}

static int	ft_set_cmd_arg(t_list *cmd_option, t_cmd *cmd)
{
	t_list	*cmd_option_temp;
	int		i;

	i = 1;
	cmd->arg = (char **)malloc(sizeof(char *) * (2 + ft_lstsize(cmd_option)));
	if (cmd->arg == NULL)
		return (EXIT_FAILURE);
	cmd->arg[0] = ft_strdup(cmd->name);
	if (cmd->arg[0] == NULL)
		return (EXIT_FAILURE);
	while (cmd_option != NULL)
	{
		cmd->arg[i++] = (char *)cmd_option->content;
		cmd_option_temp = cmd_option->next;
		free(cmd_option);
		cmd_option = cmd_option_temp;
	}
	cmd->arg[i] = NULL;
	return (EXIT_SUCCESS);
}

static int	ft_set_cmd_redirection_tab(t_list *list_cmd,
	char ***cmd_redirection_tab)
{
	t_list	*list_cmd_temp;
	int		i;

	i = 0;
	*cmd_redirection_tab
		= (char **)malloc(sizeof(char *) * (1 + ft_lstsize(list_cmd)));
	if (*cmd_redirection_tab == NULL)
		return (EXIT_FAILURE);
	while (list_cmd != NULL)
	{
		(*cmd_redirection_tab)[i++] = (char *)list_cmd->content;
		list_cmd_temp = list_cmd->next;
		free(list_cmd);
		list_cmd = list_cmd_temp;
	}
	(*cmd_redirection_tab)[i] = NULL;
	return (EXIT_SUCCESS);
}

int	ft_set_cmd_in_out_arg(t_cmd *cmd, t_list *cmd_in, t_list *cmd_out,
	t_list *cmd_option)
{
	if (ft_set_cmd_redirection_tab(cmd_in, &cmd->in))
		return (EXIT_FAILURE);
	if (ft_set_cmd_redirection_tab(cmd_out, &cmd->out))
		return (EXIT_FAILURE);
	if (ft_set_cmd_arg(cmd_option, cmd))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
