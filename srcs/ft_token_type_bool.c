/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_type_bool.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 21:22:14 by lethomas          #+#    #+#             */
/*   Updated: 2024/03/07 14:13:17 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_bool	ft_token_is_cmd_op(t_token *token)
{
	if (token->type == pipe_operator
		|| token->type == and_operator
		|| token->type == or_operator)
		return (true);
	return (false);
}

t_bool	ft_token_is_redirection_op(t_token *token)
{
	if (token->type == redirection_in
		|| token->type == redirection_here_doc
		|| token->type == redirection_out
		|| token->type == redirection_append)
		return (true);
	return (false);
}

t_token_type	ft_get_token_type(char *str)
{
	if (str[0] == '\0')
		return (word);
	else if (str[0] == '(')
		return (left_parenthesis);
	else if (str[0] == ')')
		return (right_parenthesis);
	else if (str[0] == '|' && str[1] != '|')
		return (pipe_operator);
	else if (str[0] == '<' && str[1] != '<')
		return (redirection_in);
	else if (str[0] == '>' && str[1] != '>')
		return (redirection_out);
	else if (str[0] == '|' && str[1] == '|')
		return (or_operator);
	else if (str[0] == '&' && str[1] == '&')
		return (and_operator);
	else if (str[0] == '<' && str[1] == '<')
		return (redirection_here_doc);
	else if (str[0] == '>' && str[1] == '>')
		return (redirection_append);
	else
		return (word);
}
