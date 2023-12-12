/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 04:56:11 by lethomas          #+#    #+#             */
/*   Updated: 2023/12/12 02:14:38 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_list	*token_list;
	char	*arg;
	t_list	*token_list_temp;

	if (argc != 2)
		return (EXIT_FAILURE);
	arg = ft_strdup(argv[1]);
	if (ft_create_token_list(arg, &token_list))
		return (EXIT_FAILURE);
	if (ft_check_cmd_validity(token_list))
		return (EXIT_FAILURE);
	if (ft_parenthesis_redirection(token_list))
		return (EXIT_FAILURE);
	if (ft_check_redirection_validity(token_list))
		return (EXIT_FAILURE);
	token_list_temp = token_list;
	while (token_list_temp != NULL)
	{
		printf("-%s- %d\n", ((t_token *)token_list_temp->content)->value,
			((t_token *)token_list_temp->content)->type);
		token_list_temp = token_list_temp->next;
	}
	ft_free_token_list(&token_list);
	return (EXIT_SUCCESS);
}

//token vide en fin de cmd line
//revoir l ordre de verification dernier token cmd op et check validity
//assignation cmd
