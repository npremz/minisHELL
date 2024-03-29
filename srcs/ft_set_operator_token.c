/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_operator_token.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 21:14:22 by lethomas          #+#    #+#             */
/*   Updated: 2024/03/13 17:03:43 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_operator_token_error_following(t_token *token,
	t_error_flag *error_flag)
{
	if (ft_token_is_cmd_op(token))
	{
		if (error_flag->cmd_size == 0)
			return (EXIT_FAILURE);
		error_flag->cmd_size = 0;
		error_flag->is_prev_token_a_cmd_op = true;
	}
	else
	{
		error_flag->is_prev_token_a_cmd_op = false;
		error_flag->cmd_size += 2;
	}
	if (ft_token_is_redirection_op(token))
		error_flag->is_prev_token_a_redirection = true;
	return (EXIT_SUCCESS);
}

static int	ft_get_next_token(t_token *token, char *command_line, char **str)
{
	int	len;

	if (token->type == redirection_append
		|| token->type == redirection_here_doc
		|| token->type == and_operator
		|| token->type == or_operator)
		len = 2;
	else
		len = 1;
	*str = (char *)malloc((len + 1) * sizeof(char));
	if (*str == NULL)
		return (EXIT_FAILURE);
	ft_strlcpy(*str, command_line, len + 1);
	return (EXIT_SUCCESS);
}

static int	ft_operator_token_error(t_token *token,
	t_error_flag *error_flag)
{
	if (error_flag->is_prev_token_a_redirection == true)
		return (EXIT_FAILURE);
	if (token->type == left_parenthesis)
	{
		error_flag->parenthesis_counter++;
		if (error_flag->is_prev_token_a_left_parenthesis == false
			&& error_flag->is_prev_token_a_cmd_op == false)
			return (EXIT_FAILURE);
		error_flag->is_prev_token_a_left_parenthesis = true;
	}
	if (token->type == right_parenthesis)
	{
		error_flag->parenthesis_counter--;
		error_flag->do_follow_right_parenthesis = true;
		if (error_flag->is_prev_token_a_cmd_op == true
			|| error_flag->parenthesis_counter < 0
			|| error_flag->is_prev_token_a_left_parenthesis == true)
			return (EXIT_FAILURE);
	}
	if (!(ft_token_is_redirection_op(token)
			|| token->type == right_parenthesis))
		error_flag->do_follow_right_parenthesis = false;
	if (ft_operator_token_error_following(token, error_flag))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_set_operator_token(char **command_line, int *cursor_pos, t_token *token,
	t_error_flag *error_flag)
{
	int	token_begin_pos;

	token_begin_pos = *cursor_pos;
	if (token->type == redirection_here_doc)
		error_flag->is_prev_token_a_heredoc = true;
	if (ft_operator_token_error(token, error_flag))
	{
		if (ft_get_next_token(token, *command_line + *cursor_pos,
				&error_flag->error_arg))
			return (EXIT_FAILURE);
		return (EXIT_FAILURE);
	}
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
	return (EXIT_SUCCESS);
}
