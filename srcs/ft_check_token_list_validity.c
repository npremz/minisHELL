/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_token_list_validity.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 01:13:16 by lethomas          #+#    #+#             */
/*   Updated: 2023/12/12 01:35:53 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

int	ft_check_cmd_validity(t_list *token_list)
{
	int	cmd_nb_token;

	cmd_nb_token = 0;
	while (token_list != NULL)
	{
		if (((t_token *)token_list->content)->type != pipe_operator
			&& ((t_token *)token_list->content)->type != and_operator
			&& ((t_token *)token_list->content)->type != or_operator)
			cmd_nb_token++;
		else
		{
			if (cmd_nb_token == 0)
				return (EXIT_FAILURE);
			cmd_nb_token = 0;
		}
		token_list = token_list->next;
	}
	return (EXIT_SUCCESS);
}

int	ft_check_redirection_validity(t_list *token_list)
{
	while (token_list != NULL)
	{
		if (((t_token *)token_list->content)->type == redirection_in
			|| ((t_token *)token_list->content)->type == redirection_here_doc
			|| ((t_token *)token_list->content)->type == redirection_out
			|| ((t_token *)token_list->content)->type == redirection_append)
		{
			if (token_list->next == NULL
				|| ((t_token *)token_list->next->content)->type != word)
				return (EXIT_FAILURE);
			token_list = token_list->next;
		}
		token_list = token_list->next;
	}
	return (EXIT_SUCCESS);
}
