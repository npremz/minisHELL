/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unclosed_command_line.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 20:07:48 by lethomas          #+#    #+#             */
/*   Updated: 2024/03/07 14:13:17 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_unclosed_parenthesis(char **command_line,
	t_error_flag error_flag)
{
	char	*str;
	int		i;

	str = ft_strdup("");
	if (str == NULL)
		return (EXIT_FAILURE);
	while (error_flag.parenthesis_counter > 0)
	{
		i = 0;
		ft_printf(">");
		*command_line = ft_strjoin(*command_line, str, true, true);
		if (*command_line == NULL)
			return (EXIT_FAILURE);
		str = get_next_line(0);
		if (str == NULL)
			return (EXIT_FAILURE);
		str[ft_strlen(str) - 1] = '\0';
		while (str[i] != '\0')
			if (str[i++] == ')')
				error_flag.parenthesis_counter--;
	}
	*command_line = ft_strjoin(*command_line, str, true, true);
	if (*command_line == NULL)
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
	int cursor_pos, t_token *token)
{
	char	*str;
	t_bool	do_continue;

	do_continue = true;
	if (ft_token_is_cmd_op(token)
		&& ft_is_the_last_token(*command_line, cursor_pos))
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
	return (EXIT_SUCCESS);
}

int	ft_unclosed_command_line(t_token *token, char **command_line,
	t_error_flag error_flag, int cursor_pos)
{
	if ((*command_line)[cursor_pos] == '\0'
		&& error_flag.parenthesis_counter != 0)
	{
		if (ft_unclosed_parenthesis(command_line, error_flag))
			return (EXIT_FAILURE);
	}
	else
		if (ft_cmd_op_last_token(command_line, cursor_pos, token))
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
