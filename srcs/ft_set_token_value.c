/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_token_value.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 00:33:26 by lethomas          #+#    #+#             */
/*   Updated: 2024/03/07 19:16:43 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_set_token_env_eff_list(t_token *token, t_bool is_env_effective)
{
	t_list	*new_elem;
	t_bool	*is_env_effective_alloc;

	is_env_effective_alloc = (t_bool *)malloc(sizeof(t_bool));
	if (is_env_effective_alloc == NULL)
		return (EXIT_FAILURE);
	*is_env_effective_alloc = is_env_effective;
	new_elem = ft_lstnew(is_env_effective_alloc);
	if (new_elem == NULL)
		return (EXIT_FAILURE);
	ft_lstadd_back(&token->env_eff_list, new_elem);
	return (EXIT_SUCCESS);
}

int	ft_set_token_wildcard_list(t_token *token, t_bool is_wildcard_effective)
{
	t_list	*new_elem;
	t_bool	*is_wildcard_effective_alloc;

	is_wildcard_effective_alloc = (t_bool *)malloc(sizeof(t_bool));
	if (is_wildcard_effective_alloc == NULL)
		return (EXIT_FAILURE);
	*is_wildcard_effective_alloc = is_wildcard_effective;
	new_elem = ft_lstnew(is_wildcard_effective_alloc);
	if (new_elem == NULL)
		return (EXIT_FAILURE);
	ft_lstadd_back(&token->wildcard_list, new_elem);
	return (EXIT_SUCCESS);
}

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
