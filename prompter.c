/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npremont <npremont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 11:36:05 by npremont          #+#    #+#             */
/*   Updated: 2023/12/13 18:42:30 by npremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	int		pid;

	if (ft_envinit(envp) == -1)
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
		pid = fork();
		if (pid == -1)
			return (write(2, "Process error\n", 14), 1);
		if (pid == 0)
		{
			if (ft_strncmp(line, "env", 3) == 0)
				ft_env();
			if (ft_strncmp(line, "export", 6) == 0)
				ft_export(line);
		}
		free(line);
		waitpid(pid, NULL, 0);
	}
	ft_lstclear(&env_list, free);
	return (0);
}
