/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npremont <npremont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 11:36:05 by npremont          #+#    #+#             */
/*   Updated: 2023/12/18 18:46:35 by npremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	int		pid;
	char	**en;

	en = ft_envinit(envp, en);
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
			ft_cd(line, en);
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
	ft_free_split(en);
	return (0);
}
