/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 20:29:11 by lethomas          #+#    #+#             */
/*   Updated: 2024/03/07 17:28:44 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_check_access_then_exec(char *cmd_path, t_cmd *cmd, t_list **env)
{
	char	**env_tab;
	
	env_tab = ft_en_to_tab(*env);
	if (env_tab == NULL)
		return (EXIT_FAILURE);
	if (access(cmd_path, X_OK) == 0)
		if (execve(cmd_path, cmd->arg, env_tab) == -1)
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	ft_exec_env_path(t_cmd *cmd, t_list **env)
{
	int		i;
	char	*path_line;
	char	**path_tab;

	i = 0;
	path_line = ft_get_gvar_value("PATH", *env);
	if (path_line == NULL)
		return (EXIT_FAILURE);
	path_tab = ft_split(path_line, ':');
	if (path_tab == NULL)
		return (EXIT_FAILURE);
	while (path_tab[i] != NULL)
	{
		path_tab[i] = ft_strjoin(path_tab[i], "/", true, false);
		if (path_tab[i] == NULL)
			return (EXIT_FAILURE);
		path_tab[i] = ft_strjoin(path_tab[i], cmd->name, true, false);
		if (path_tab[i] == NULL)
			return (EXIT_FAILURE);
		if (ft_check_access_then_exec(path_tab[i], cmd, env))
			return (EXIT_FAILURE);
		free(path_tab[i++]);
	}
	free(path_tab);
	return (EXIT_SUCCESS);
}

static int	ft_exec_current_work_directory_path(t_cmd *cmd, t_list **env)
{
	char	*current_work_directory;

	current_work_directory = (char *)malloc(MAX_CWD_PATH_SIZE * sizeof(char));
	if (current_work_directory == NULL)
		return (EXIT_FAILURE);
	if (getcwd(current_work_directory, MAX_CWD_PATH_SIZE) == NULL)
		return (EXIT_FAILURE);
	current_work_directory = ft_strjoin(current_work_directory, "/",
			true, false);
	if (current_work_directory == NULL)
		return (EXIT_FAILURE);
	current_work_directory = ft_strjoin(current_work_directory, cmd->name,
			true, false);
	if (current_work_directory == NULL)
		return (EXIT_FAILURE);
	if (ft_check_access_then_exec(current_work_directory, cmd, env))
		return (EXIT_FAILURE);
	free(current_work_directory);
	return (EXIT_SUCCESS);
}

int	ft_exec(t_cmd *cmd, char **error_arg, t_list **env)
{
	if (ft_strncmp(cmd->name, "./", 2) == 0)
	{
		if (ft_exec_current_work_directory_path(cmd, env))
			return (EXIT_FAILURE);
	}
	else if (cmd->name[0] == '/')
	{
		if (ft_check_access_then_exec(cmd->name, cmd, env))
			return (EXIT_FAILURE);
	}
	else
		if (ft_exec_env_path(cmd, env))
			return (EXIT_FAILURE);
	*error_arg = ft_strdup(cmd->name);
	errno = 200;
	return (EXIT_FAILURE);
}
