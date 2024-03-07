/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_word_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 21:11:12 by lethomas          #+#    #+#             */
/*   Updated: 2024/03/07 14:13:17 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_bool	ft_str_is_an_op(char *command_line)
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

static int	ft_look_for_special_char(char *command_line, t_token *token,
	t_bool is_there_quote, t_bool is_first_char)
{
	if (*command_line == '$')
		(void)token;
	if (*command_line == '*')
		if (ft_set_token_wildcard_list(token, true))
			return (EXIT_FAILURE);
	if (*command_line == '='
		&& is_there_quote == false)
	{
		token->type = assignation;
		if (is_first_char == true)
			return (ft_putendl_fd("assignation var vide", 2), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	ft_look_for_quote(char **command_line, int *cursor_pos,
	t_token *token, int *token_begin_pos)
{
	if ((*command_line)[*cursor_pos] == '\'')
		if (ft_single_quote(command_line, cursor_pos, token,
				token_begin_pos))
			return (EXIT_FAILURE);
	if ((*command_line)[*cursor_pos] == '"')
		if (ft_double_quote(command_line, cursor_pos, token,
				token_begin_pos))
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	ft_word_token_error(t_error_flag *error_flag,
	t_bool *is_there_quote, t_bool *is_first_char)
{
	error_flag->cmd_size++;
	if (error_flag->do_follow_right_parenthesis == true
		&& error_flag->is_prev_token_a_redirection == false)
		return (ft_putendl_fd("rigtht_parenthesis error", 2), EXIT_FAILURE);
	error_flag->is_prev_token_a_redirection = false;
	error_flag->is_prev_token_a_left_parenthesis = false;
	error_flag->is_prev_token_a_cmd_op = false;
	*is_there_quote = false;
	*is_first_char = true;
	return (EXIT_SUCCESS);
}

int	ft_set_word_token(char **command_line, int *cursor_pos, t_token *token,
	t_error_flag *error_flag)
{
	int		token_begin_pos;
	t_bool	is_there_quote;
	t_bool	is_first_char;

	token_begin_pos = *cursor_pos;
	if (ft_word_token_error(error_flag, &is_there_quote, &is_first_char))
		return (EXIT_FAILURE);
	while ((*command_line)[*cursor_pos] != '\0'
		&& (*command_line)[*cursor_pos] != ' '
		&& !ft_str_is_an_op(*command_line + *cursor_pos))
	{
		if ((*command_line)[*cursor_pos] == '\''
			|| (*command_line)[*cursor_pos] == '\"')
			is_there_quote = true;
		if (ft_look_for_quote(command_line, cursor_pos, token,
				&token_begin_pos))
			return (EXIT_FAILURE);
		if (ft_look_for_special_char(*command_line + (*cursor_pos)++, token,
				is_there_quote, is_first_char))
			return (EXIT_FAILURE);
		is_first_char = false;
	}
	if (ft_set_token_value(*command_line, token_begin_pos, *cursor_pos, token))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}