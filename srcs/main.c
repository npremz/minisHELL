/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 04:56:11 by lethomas          #+#    #+#             */
/*   Updated: 2023/12/12 18:42:21 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_list	*token_list;
	t_list	*cmd_list;
	char	*arg;
	t_list	*list_temp;

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
	list_temp = token_list;
	while (list_temp != NULL)
	{
		printf("-%s- %d\n", ((t_token *)list_temp->content)->value,
			((t_token *)list_temp->content)->type);
		list_temp = list_temp->next;
	}
	printf("\n\n\n");
	if (ft_create_cmd_list(token_list, &cmd_list))
		return (EXIT_FAILURE);
	list_temp = cmd_list;
	while (list_temp != NULL)
	{
		printf("%d name:%s in:%s out:%s\n", ((t_cmd *)list_temp->content)->type,
			((t_cmd *)list_temp->content)->name,
			((t_cmd *)list_temp->content)->in,
			((t_cmd *)list_temp->content)->out);
		list_temp = list_temp->next;
	}
	return (EXIT_SUCCESS);
}

//token vide en fin de cmd line
//revoir l ordre de verification dernier token cmd op et check validity
//assignation cmd
//recuperer plusieurs redirection a la fois, pour ouvir ect...
//car en red out cree meme si n ecrit pas et en in ouvre meme si n ecrit pas
