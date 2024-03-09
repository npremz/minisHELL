/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 04:56:11 by lethomas          #+#    #+#             */
/*   Updated: 2024/03/09 14:49:37 by lethomas         ###   ########.fr       */
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
			if (ft_exec_cmd_line(line, &en))
				return (EXIT_FAILURE);
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
