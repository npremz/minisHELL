/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npremont <npremont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 11:36:05 by npremont          #+#    #+#             */
/*   Updated: 2023/12/21 00:04:50 by npremont         ###   ########.fr       */
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
		add_history(line);
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
		if (ft_strncmp(line, "env", 3) == 0)
			ft_env(en);
		free(line);
	}
	ft_free_split(en);
	return (0);
}
