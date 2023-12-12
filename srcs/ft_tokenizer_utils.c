/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizer_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 00:33:26 by lethomas          #+#    #+#             */
/*   Updated: 2023/12/10 08:06:07 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

int	ft_set_token_value(char *command_line, int token_begin_pos,
	int cursor_pos, t_token *token)
{
	char	*token_value;

	token_value = (char *)malloc((cursor_pos - token_begin_pos + 1)
			* sizeof(char));
	if (token_value == NULL)
		return (EXIT_FAILURE);
	ft_strlcpy(token_value, command_line + token_begin_pos,
		cursor_pos - token_begin_pos + 1);
	if (token->value == NULL)
		token->value = token_value;
	else
	{
		token->value = ft_strjoin(token->value, token_value, true, true);
		if (token->value == NULL)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	ft_add_new_token(t_list **token_list, t_token *token)
{
	t_list	*token_list_elem;

	if (token->value == NULL)
	{
		ft_free_token((void *)token);
		return (EXIT_SUCCESS);
	}
	token_list_elem = ft_lstnew(token);
	if (token_list_elem == NULL)
		return (EXIT_FAILURE);
	ft_lstadd_back(token_list, token_list_elem);
	return (EXIT_SUCCESS);
}

static t_token_type	ft_get_token_type_2(char *str)
{
	if (str[0] == '|'
		&& str[1] == '|')
		return (or_operator);
	else if (str[0] == '&'
		&& str[1] == '&')
		return (and_operator);
	else if (str[0] == '<'
		&& str[1] == '<')
		return (redirection_here_doc);
	else if (str[0] == '>'
		&& str[1] == '>')
		return (redirection_append);
	else
		return (word);
}

t_token_type	ft_get_token_type(char *str)
{
	if (str[0] == '\0')
		return (word);
	else if (str[0] == '|' && str[1] != '|')
		return (pipe_operator);
	else if (str[0] == '(')
		return (left_parenthesis);
	else if (str[0] == ')')
		return (right_parenthesis);
	else if (str[0] == '<' && str[1] != '<')
		return (redirection_in);
	else if (str[0] == '>'
		&& str[1] != '>')
		return (redirection_out);
	else
		return (ft_get_token_type_2(str));
}

t_bool	ft_is_an_op(char *command_line)
{
	if (command_line[0] == '\0')
		return (false);
	else if (command_line[0] == '|'
		|| command_line[0] == '('
		|| command_line[0] == ')'
		|| command_line[0] == '<'
		|| command_line[0] == '>'
		|| (command_line[0] == '&'
			&& command_line[1] == '&'))
		return (true);
	else
		return (false);
}
