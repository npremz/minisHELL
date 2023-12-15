/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_token_value.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 00:33:26 by lethomas          #+#    #+#             */
/*   Updated: 2023/12/15 01:05:36 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing_exec.h"

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
