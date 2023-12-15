/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmd_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 23:53:09 by lethomas          #+#    #+#             */
/*   Updated: 2023/12/15 01:05:36 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing_exec.h"

// static void	printf_cmd(void *cmd)
// {
// 	int	i;

// 	i = 0;
// 	printf("%d name:%s option: ", ((t_cmd *)cmd)->type,
// 		((t_cmd *)cmd)->name);
// 	if (((t_cmd *)cmd)->arg != NULL)
// 		while (((t_cmd *)cmd)->arg[i] != NULL)
// 			printf("%s ", ((t_cmd *)cmd)->arg[i++]);
// 	printf("redirection_in: %d ", ((t_cmd *)cmd)->type_in);
// 	i = 0;
// 	if (((t_cmd *)cmd)->in != NULL)
// 		while (((t_cmd *)cmd)->in[i] != NULL)
// 			printf("%s ", ((t_cmd *)cmd)->in[i++]);
// 	printf("redirection_out: %d ", ((t_cmd *)cmd)->type_out);
// 	i = 0;
// 	if (((t_cmd *)cmd)->out != NULL)
// 		while (((t_cmd *)cmd)->out[i] != NULL)
// 			printf("%s ", ((t_cmd *)cmd)->out[i++]);
// 	printf("\n");
// }

int	ft_exec_cmd_line(char *command_line)
{
	t_list	*token_list;
	t_list	*cmd_list;
	t_btree	*cmd_tree;

	token_list = NULL;
	if (ft_create_token_list(command_line, &token_list))
		return (EXIT_FAILURE);
	if (ft_token_parenthesis(token_list))
		return (EXIT_FAILURE);
	if (ft_create_cmd_list(token_list, &cmd_list))
		return (EXIT_FAILURE);
	if (ft_create_cmd_tree(cmd_list, &cmd_tree))
		return (EXIT_FAILURE);
	if (ft_exec_cmd_tree(cmd_tree))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
//parenthese vide
//revoir l ordre de red deplacees par des parentheses
//tab pour les type de redirections
//wildcard
//var env
//ft_btree_apply_prefix(cmd_tree, &printf_cmd);
//here_doc
