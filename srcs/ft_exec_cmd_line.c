/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmd_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npremont <npremont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 23:53:09 by lethomas          #+#    #+#             */
/*   Updated: 2024/03/11 17:54:02 by npremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	printf_cmd(void *cmd)
{
	int	i;

	i = 0;
	t_list *save;
	if (cmd == NULL)
	{
		printf("null node \n");
		return ;
	}
	printf("%d name:%s", ((t_cmd *)cmd)->type,
		((t_cmd *)cmd)->name);
	save = ((t_cmd *)cmd)->env_eff_name;
	printf (" name_env_eff: ");
	while (((t_cmd *)cmd)->env_eff_name != NULL)
	{
		printf("%s ", (char *)((t_cmd *)cmd)->env_eff_name->content);
		((t_cmd *)cmd)->env_eff_name = ((t_cmd *)cmd)->env_eff_name->next;
	}
	((t_cmd *)cmd)->env_eff_name = save;
	printf (" option: ");
	if (((t_cmd *)cmd)->arg != NULL)
		while (((t_cmd *)cmd)->arg[i] != NULL)
			printf("%s ", ((t_cmd *)cmd)->arg[i++]);
	save = ((t_cmd *)cmd)->env_eff_arg;
	printf (" option_env_eff: ");
	while (((t_cmd *)cmd)->env_eff_arg != NULL)
	{
		printf("%s ", (char *)((t_cmd *)cmd)->env_eff_arg->content);
		((t_cmd *)cmd)->env_eff_arg = ((t_cmd *)cmd)->env_eff_arg->next;
	}
	((t_cmd *)cmd)->env_eff_arg = save;
	printf("redirection_in: ");
	i = 0;
	if (((t_cmd *)cmd)->in != NULL)
	{
		while (((t_cmd *)cmd)->in[i] != NULL)
		{
			printf("%d ", ((t_cmd *)cmd)->type_in[i]);
			printf("%s ", ((t_cmd *)cmd)->in[i++]);
		}
	}
	save = ((t_cmd *)cmd)->env_eff_in;
	printf (" red_in_env_eff: %p ", ((t_cmd *)cmd)->env_eff_in);
	while (((t_cmd *)cmd)->env_eff_in != NULL)
	{
		printf("%s ", (char *)((t_cmd *)cmd)->env_eff_in->content);
		((t_cmd *)cmd)->env_eff_in = ((t_cmd *)cmd)->env_eff_in->next;
	}
	((t_cmd *)cmd)->env_eff_in = save;
	printf("redirection_out: ");
	i = 0;
	if (((t_cmd *)cmd)->out != NULL)
	{
		while (((t_cmd *)cmd)->out[i] != NULL)
		{
			printf("%d ", ((t_cmd *)cmd)->type_out[i]);
			printf("%s ", ((t_cmd *)cmd)->out[i++]);
		}
	}
	printf("\n");
}

int	ft_exec_cmd_line(char *command_line, t_list **env)
{
	t_list	*token_list;
	t_list	*cmd_list;
	t_btree	*cmd_tree;

	token_list = NULL;
	if (ft_create_token_list(command_line, &token_list))
		return (EXIT_FAILURE);
	if (token_list == NULL)
		return (EXIT_SUCCESS);
	if (ft_token_parenthesis(token_list))
		return (EXIT_FAILURE);
	if (ft_create_cmd_list(token_list, &cmd_list))
		return (EXIT_FAILURE);
	if (DEBUG_MODE)
		ft_lstiter(cmd_list, &printf_cmd);
	if (ft_create_cmd_tree(cmd_list, &cmd_tree))
		return (EXIT_FAILURE);
	if (ft_exec_cmd_tree(cmd_tree, env))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
//ft_lstiter(cmd_list, &printf_cmd);
//ft_btree_apply_suffix(cmd_tree, &printf_cmd);
