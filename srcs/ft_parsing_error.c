/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:51:20 by lethomas          #+#    #+#             */
/*   Updated: 2024/03/13 17:37:51 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_set_parsing_error(char **error_parsing)
{
	*error_parsing = (char *)malloc(sizeof(char));
	(*error_parsing)[0] = '\0';
	return (EXIT_SUCCESS);
}

static int	ft_get_next_token(char *command_line, char **str)
{
	int		len;

	len = 0;
	while (command_line[len] != '\0'
		&& command_line[len] != ' '
		&& !ft_str_is_an_op(command_line + len))
	{
		len++;
		if (command_line[len] == '\'')
			while (command_line[len] != '\'')
				len++;
		if (command_line[len] == '\"')
			while (command_line[len] != '\"')
				len++;
	}
	*str = (char *)malloc((len + 1) * sizeof(char));
	if (*str == NULL)
		return (EXIT_FAILURE);
	ft_strlcpy(*str, command_line, len + 1);
	return (EXIT_SUCCESS);
}

int	ft_word_token_error(t_error_flag *error_flag,
	char *command_line, int cursor_pos)
{
	error_flag->cmd_size++;
	if (error_flag->do_follow_right_parenthesis == true
		&& error_flag->is_prev_token_a_redirection == false)
	{
		if (ft_get_next_token(command_line + cursor_pos,
				&error_flag->error_arg))
			return (EXIT_FAILURE);
		return (EXIT_FAILURE);
	}
	error_flag->is_prev_token_a_redirection = false;
	error_flag->is_prev_token_a_left_parenthesis = false;
	error_flag->is_prev_token_a_cmd_op = false;
	return (EXIT_SUCCESS);
}
