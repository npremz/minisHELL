/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_token_list.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 22:18:11 by lethomas          #+#    #+#             */
/*   Updated: 2023/12/12 02:03:34 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

static int	ft_word_token(char **command_line,
	int *cursor_pos, t_token *token, t_list **token_list)
{
	int	token_begin_pos;

	token_begin_pos = *cursor_pos;
	while ((*command_line)[*cursor_pos] != '\0'
		&& (*command_line)[*cursor_pos] != ' '
		&& !ft_is_an_op((*command_line) + *cursor_pos))
	{
		if ((*command_line)[*cursor_pos] == '\'')
			if (ft_single_quote(command_line, cursor_pos, token,
					&token_begin_pos))
				return (EXIT_FAILURE);
		if ((*command_line)[*cursor_pos] == '"')
			if (ft_double_quote(command_line, cursor_pos, token,
					&token_begin_pos))
				return (EXIT_FAILURE);
		if ((*command_line)[*cursor_pos] == '$')
			token->have_env_var = true;
		if ((*command_line)[(*cursor_pos)++] == '*')
			token->have_wildcard = true;
	}
	if (ft_set_token_value(*command_line, token_begin_pos, *cursor_pos, token))
		return (EXIT_FAILURE);
	if (ft_add_new_token(token_list, token))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	ft_is_the_last_token(char *command_line, int cursor_pos)
{
	while (command_line[cursor_pos] != '\0')
	{
		if (command_line[cursor_pos] != ' ')
			return (false);
		cursor_pos++;
	}
	return (true);
}

static int	ft_cmd_op_last_token(char **command_line,
	int *cursor_pos, t_token *token)
{
	char	*str;
	t_bool	do_continue;

	do_continue = true;
	if (token->type == pipe_operator || token->type == and_operator
		|| token->type == or_operator)
	{
		if (ft_is_the_last_token(*command_line, *cursor_pos))
		{
			while (do_continue == true)
			{
				ft_printf(">");
				str = get_next_line(0);
				if (str == NULL)
					return (EXIT_FAILURE);
				str[ft_strlen(str) - 1] = '\0';
				if (str[0] != '\0')
					do_continue = false;
				*command_line = ft_strjoin(*command_line, str, true, true);
				if (*command_line == NULL)
					return (EXIT_FAILURE);
			}
		}
	}
	return (EXIT_SUCCESS);
}

static int	ft_op_token(char **command_line,
	int *cursor_pos, t_token *token, t_list **token_list)
{
	int	token_begin_pos;

	token_begin_pos = *cursor_pos;
	if (token->type == redirection_append
		|| token->type == redirection_here_doc
		|| token->type == and_operator
		|| token->type == or_operator)
		*cursor_pos += 2;
	else
		*cursor_pos += 1;
	if (ft_set_token_value(*command_line, token_begin_pos,
			*cursor_pos, token))
		return (EXIT_FAILURE);
	if (ft_add_new_token(token_list, token))
		return (EXIT_FAILURE);
	if (ft_cmd_op_last_token(command_line, cursor_pos, token))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_create_token_list(char *command_line, t_list **token_list)
{
	int		cursor_pos;
	t_token	*token;

	cursor_pos = 0;
	*token_list = NULL;
	while (command_line[cursor_pos] != '\0')
	{
		token = (t_token *)malloc(sizeof(t_token));
		if (token == NULL)
			return (EXIT_FAILURE);
		ft_bzero(token, sizeof(t_token));
		while (command_line[cursor_pos] == ' ')
			cursor_pos++;
		token->type = ft_get_token_type(command_line + cursor_pos);
		if (token->type == word)
		{
			if (ft_word_token(&command_line, &cursor_pos, token, token_list))
				return (EXIT_FAILURE);
		}
		else
			if (ft_op_token(&command_line, &cursor_pos, token, token_list))
				return (EXIT_FAILURE);
	}
	free(command_line);
	return (EXIT_SUCCESS);
}
