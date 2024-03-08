/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_cmd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 23:44:56 by lethomas          #+#    #+#             */
/*   Updated: 2024/03/08 13:50:56 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_set_cmd_redirection_list(t_list **wildcard_cmd_list,
	t_list *token_list, t_list **list_cmd_redirection, t_list **env_eff_list)
{
	t_list			*elem_redirection_list;
	char			*redirection_value;
	t_token_type	*redirection_type;

	redirection_type = &((t_token *)token_list->content)->type;
	elem_redirection_list = ft_lstnew(redirection_type);
	if (elem_redirection_list == NULL)
		return (EXIT_FAILURE);
	ft_lstadd_back(list_cmd_redirection, elem_redirection_list);
	redirection_value
		= ft_strdup(((t_token *)token_list->next->content)->value);
	if (redirection_value == NULL)
		return (EXIT_FAILURE);
	elem_redirection_list = ft_lstnew(redirection_value);
	if (elem_redirection_list == NULL)
		return (EXIT_FAILURE);
	ft_lstadd_back(list_cmd_redirection, elem_redirection_list);
	ft_lstadd_back(wildcard_cmd_list,
		((t_token *)token_list->next->content)->wildcard_list);
	ft_lstadd_back(env_eff_list,
		((t_token *)token_list->next->content)->env_eff_list);
	return (EXIT_SUCCESS);
}

int	ft_set_cmd_redirection(t_cmd *cmd, t_list **token_list,
	t_list **list_cmd_in, t_list **list_cmd_out)
{
	if (((t_token *)(*token_list)->content)->type == redirection_here_doc
		|| ((t_token *)(*token_list)->content)->type == redirection_in)
	{
		if (ft_set_cmd_redirection_list(&cmd->wildcard_in, *token_list,
				list_cmd_in, &cmd->env_eff_in))
			return (EXIT_FAILURE);
	}
	else
		if (ft_set_cmd_redirection_list(&cmd->wildcard_out, *token_list,
				list_cmd_out, &cmd->env_eff_out))
			return (EXIT_FAILURE);
	*token_list = (*token_list)->next;
	return (EXIT_SUCCESS);
}

static int	ft_set_cmd_arg(t_list *cmd_option, t_cmd *cmd)
{
	t_list	*cmd_option_temp;
	int		i;

	i = 1;
	if (cmd->name == NULL)
		return (EXIT_SUCCESS);
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
	char ***cmd_redirection_tab, t_token_type **cmd_redirection_type_tab)
{
	int		i;
	t_list	*temp_elem;

	i = 0;
	*cmd_redirection_type_tab = (t_token_type *)malloc(sizeof(t_token_type)
			* (ft_lstsize(list_cmd) / 2));
	if (*cmd_redirection_type_tab == NULL)
		return (EXIT_FAILURE);
	*cmd_redirection_tab = (char **)malloc(sizeof(char *)
			* (1 + ft_lstsize(list_cmd) / 2));
	if (*cmd_redirection_tab == NULL)
		return (EXIT_FAILURE);
	while (list_cmd != NULL)
	{
		(*cmd_redirection_type_tab)[i] = *(t_token_type *)list_cmd->content;
		(*cmd_redirection_tab)[i++] = (char *)list_cmd->next->content;
		temp_elem = list_cmd;
		list_cmd = list_cmd->next->next;
		free(temp_elem->next);
		free(temp_elem);
	}
	(*cmd_redirection_tab)[i] = NULL;
	return (EXIT_SUCCESS);
}

int	ft_set_cmd_in_out_arg(t_cmd *cmd, t_list *cmd_in, t_list *cmd_out,
	t_list *cmd_option)
{
	if (ft_set_cmd_redirection_tab(cmd_in, &cmd->in, &cmd->type_in))
		return (EXIT_FAILURE);
	if (ft_set_cmd_redirection_tab(cmd_out, &cmd->out, &cmd->type_out))
		return (EXIT_FAILURE);
	if (ft_set_cmd_arg(cmd_option, cmd))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
