/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npremont <npremont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 04:56:11 by lethomas          #+#    #+#             */
/*   Updated: 2024/03/07 13:58:56 by npremont         ###   ########.fr       */
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
	signal(SIGINT, ft_sighandle);
	while (1)
	{
		line = readline("minishell> ");
		if (line)
		{
			add_history(line);
			ft_exec_cmd_line(line, &en);
		}
	}
	return (EXIT_SUCCESS);
}

//heredoc controlD									
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
