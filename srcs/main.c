/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npremont <npremont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 04:56:11 by lethomas          #+#    #+#             */
/*   Updated: 2024/03/14 18:48:03 by npremont         ###   ########.fr       */
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
	g_sig.sigint = 0;
	ft_define_ctrl_c();
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		ft_mute_term();
		line = readline("minishell> ");
		if (!line)
			ft_exit(&en, NULL, false);
		else if (line)
		{
			ft_unmute_term();
			add_history(line);
			g_sig.sigint = 1;
			signal(SIGINT, ft_null);
			ft_exec_cmd_line(line, &en);
			signal(SIGINT, ft_new_prompt);
			g_sig.sigint = 0;
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
