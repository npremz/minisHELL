/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 01:49:42 by lethomas          #+#    #+#             */
/*   Updated: 2024/03/14 18:40:50 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_check_for_quote(char **command_line, int cursor_pos, char quote)
{
	char	*str;

	if (ft_strchr(*command_line + cursor_pos, quote) != NULL)
		return (EXIT_SUCCESS);
	else
	{
		str = ft_strdup("\n");
		if (str == NULL)
			return (EXIT_FAILURE);
		while (ft_strchr(str, quote) == NULL)
		{
			*command_line = ft_strjoin(*command_line, str, true, true);
			if (*command_line == NULL)
				return (EXIT_FAILURE);
			ft_printf(">");
			str = get_next_line(0);
			if (str == NULL)
				return (EXIT_FAILURE);
		}
		str[ft_strlen(str) - 1] = '\0';
		*command_line = ft_strjoin(*command_line, str, true, true);
		if (*command_line == NULL)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	ft_single_quote_routine(char *command_line,
	t_token *token, int *cursor_pos)
{
	int	token_begin_pos;

	token_begin_pos = *cursor_pos;
	while (command_line[*cursor_pos] != '\'')
	{
		if (command_line[*cursor_pos] == '$')
			if (ft_set_token_env_eff_list(command_line, token, false))
				return (EXIT_FAILURE);
		if (command_line[*cursor_pos] == '*')
			if (ft_set_token_wildcard_list(token, false))
				return (EXIT_FAILURE);
		(*cursor_pos)++;
	}
	if (ft_set_token_value(command_line, token_begin_pos,
			*cursor_pos, token))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_single_quote(char **command_line, int *cursor_pos,
	t_token *token, int *token_begin_pos)
{
	if (ft_set_token_value(*command_line, *token_begin_pos,
			*cursor_pos, token))
		return (EXIT_FAILURE);
	(*cursor_pos)++;
	if (ft_check_for_quote(command_line, *cursor_pos, '\''))
		return (EXIT_FAILURE);
	if (ft_single_quote_routine(*command_line, token, cursor_pos))
		return (EXIT_FAILURE);
	*token_begin_pos = *cursor_pos + 1;
	return (EXIT_SUCCESS);
}

static int	ft_double_quote_routine(char *command_line,
	t_token *token, int *cursor_pos)
{
	int	token_begin_pos;

	token_begin_pos = *cursor_pos;
	while (command_line[*cursor_pos] != '"')
	{
		if (command_line[*cursor_pos] == '$')
			if (ft_set_token_env_eff_list(command_line + *cursor_pos,
					token, true))
				return (EXIT_FAILURE);
		if (command_line[*cursor_pos] == '*')
			if (ft_set_token_wildcard_list(token, false))
				return (EXIT_FAILURE);
		(*cursor_pos)++;
	}
	if (ft_set_token_value(command_line, token_begin_pos,
			*cursor_pos, token))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_double_quote(char **command_line, int *cursor_pos,
	t_token *token, int *token_begin_pos)
{
	if (ft_set_token_value(*command_line, *token_begin_pos,
			*cursor_pos, token))
		return (EXIT_FAILURE);
	(*cursor_pos)++;
	if (ft_check_for_quote(command_line, *cursor_pos, '"'))
		return (EXIT_FAILURE);
	if (ft_double_quote_routine(*command_line, token, cursor_pos))
		return (EXIT_FAILURE);
	*token_begin_pos = *cursor_pos + 1;
	return (EXIT_SUCCESS);
}
