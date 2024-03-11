/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npremont <npremont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 04:56:11 by lethomas          #+#    #+#             */
/*   Updated: 2024/03/11 16:25:31 by npremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_list	*en;

	(void)argc;
	(void)argv;
	line = NULL;
	en = NULL;
	ft_envinit(&en, envp);
	signal(SIGINT, ft_new_prompt);
	signal(SIGQUIT, ft_null);
	while (1)
	{
		ft_mute_term();
		line = readline("minishell> ");
		if (!line)
			ft_exit(&en, false);
		else if (line)
		{
			ft_unmute_term();
			add_history(line);
			signal(SIGINT, ft_kill_process);
			ft_exec_cmd_line(line, &en);
			signal(SIGINT, ft_new_prompt);
		}
	}
	return (EXIT_SUCCESS);
}

//heredoc controlD, env_var et ordre
//getenv fils de fils
//parenthese vide
//./Makefile ne fonctionne pas

// int	main(int argc, char **argv)
// {
// 	if (main2(argc, argv))
// 		return (EXIT_FAILURE);
// 	system("leaks parsing");
// 	return (EXIT_SUCCESS);
// }
