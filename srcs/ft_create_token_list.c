/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_token_list.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 22:18:11 by lethomas          #+#    #+#             */
/*   Updated: 2023/12/15 20:36:21 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing_exec.h"

static t_error_flag	ft_init_error_flag(void)
{
	t_error_flag	error_flag;

	error_flag.cmd_size = 0;
	error_flag.is_prev_token_a_redirection = false;
	error_flag.is_prev_token_a_left_parenthesis = false;
	error_flag.do_follow_right_parenthesis = false;
	error_flag.is_prev_token_a_cmd_op = true;
	error_flag.parenthesis_counter = 0;
	return (error_flag);
}

static int	ft_set_token(char **command_line, int *cursor_pos, t_token *token,
	t_error_flag *error_flag)
{
	token->type = ft_get_token_type(*command_line + *cursor_pos);
	if (token->type == word)
	{
		if (ft_set_word_token(command_line, cursor_pos, token, error_flag))
			return (EXIT_FAILURE);
	}
	else
		if (ft_set_operator_token(command_line, cursor_pos, token,
				error_flag))
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	ft_add_new_token(t_list **token_list, t_token *token)
{
	t_list	*token_list_elem;

	token_list_elem = ft_lstnew(token);
	if (token_list_elem == NULL)
		return (EXIT_FAILURE);
	ft_lstadd_back(token_list, token_list_elem);
	return (EXIT_SUCCESS);
}

static t_bool	ft_trim_command_line(t_token *token, char *command_line,
	int *cursor_pos)
{
	while (command_line[*cursor_pos] == ' ')
		(*cursor_pos)++;
	if (command_line[*cursor_pos] == '\0')
	{
		free(token);
		return (true);
	}
	return (false);
}

int	ft_create_token_list(char *command_line, t_list **token_list)
{
	int				cursor_pos;
	t_token			*token;
	t_error_flag	error_flag;

	cursor_pos = 0;
	error_flag = ft_init_error_flag();
	while (command_line[cursor_pos] != '\0')
	{
		token = (t_token *)ft_calloc(1, sizeof(t_token));
		if (token == NULL)
			return (EXIT_FAILURE);
		if (ft_trim_command_line(token, command_line, &cursor_pos))
			break ;
		if (ft_set_token(&command_line, &cursor_pos, token, &error_flag))
			return (EXIT_FAILURE);
		if (ft_add_new_token(token_list, token))
			return (EXIT_FAILURE);
		if (ft_unclosed_command_line(token, &command_line, error_flag,
				cursor_pos))
			return (EXIT_FAILURE);
	}
	if (error_flag.is_prev_token_a_redirection == true)
		return (ft_putendl_fd("redirection vide", 2), EXIT_FAILURE);
	free(command_line);
	return (EXIT_SUCCESS);
}
