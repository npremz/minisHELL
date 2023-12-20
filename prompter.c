/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npremont <npremont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 11:36:05 by npremont          #+#    #+#             */
/*   Updated: 2023/12/20 18:26:35 by npremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	int		pid;
	char	**en;
	char	**test_cd;
	char	**test_exp;

	en = ft_envinit(envp);
	if (!en)
		return (write(2, "Memory error\n", 14), 1);
	pid = 50;
	while (pid != 0)
	{
		line = readline("minishell> ");
		if (ft_strncmp(line, "exit", 4) == 0)
		{
			free(line);
			break ;
		}
		if (ft_strncmp(line, "cd", 2) == 0)
		{
			test_cd = ft_split(line, ' ');
			ft_cd(test_cd, &en);
		}
		if (ft_strncmp(line, "export", 6) == 0)
		{
			test_exp = ft_split(line, ' ');
			ft_export(test_exp, &en);
		}
		if (ft_strncmp(line, "pwd", 3) == 0)
			ft_pwd();
		pid = fork();
		if (pid == -1)
			return (write(2, "Process error\n", 14), 1);
		if (pid == 0)
		{
			if (ft_strncmp(line, "env", 3) == 0)
				ft_env(en);
		}
		free(line);
		waitpid(pid, NULL, 0);
	}
	return (0);
}
