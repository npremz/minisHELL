/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 20:29:11 by lethomas          #+#    #+#             */
/*   Updated: 2023/12/15 01:05:36 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing_exec.h"

static int	ft_set_exec_path(char ***path_tab)
{
	int		i;
	char	*path_line;

	i = 0;
	path_line = getenv("PATH");
	if (path_line == NULL)
		return (EXIT_FAILURE);
	*path_tab = ft_split(path_line, ':');
	if (*path_tab == NULL)
		return (EXIT_FAILURE);
	while ((*path_tab)[i] != NULL)
	{
		(*path_tab)[i] = ft_strjoin((*path_tab)[i], "/", true, false);
		if ((*path_tab)[i++] == NULL)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static void	ft_free_exec_path(char **exec_path)
{
	int	i;

	i = 0;
	while (exec_path[i] != NULL)
		free(exec_path[i++]);
	free(exec_path);
}

static int	ft_check_access_then_exec(char *cmd_path, t_cmd *cmd)
{
	if (access(cmd_path, X_OK) == 0)
		if (execve(cmd_path, cmd->arg, NULL) == -1)
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_exec(t_cmd *cmd, char **error_arg)
{
	int		i;
	char	**exec_path;

	i = 0;
	if (ft_set_exec_path(&exec_path))
		return (EXIT_FAILURE);
	if (ft_check_access_then_exec(cmd->name, cmd))
		return (EXIT_FAILURE);
	while (exec_path[i] != NULL)
	{
		exec_path[i] = ft_strjoin(exec_path[i], cmd->name, true, false);
		if (exec_path[i] == NULL)
			return (EXIT_FAILURE);
		if (ft_check_access_then_exec(exec_path[i], cmd))
			return (EXIT_FAILURE);
		i++;
	}
	ft_free_exec_path(exec_path);
	*error_arg = ft_strdup(cmd->name);
	errno = 200;
	return (EXIT_FAILURE);
}
