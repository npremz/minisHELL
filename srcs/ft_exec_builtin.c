/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 12:33:40 by npremont          #+#    #+#             */
/*   Updated: 2024/03/07 16:25:24 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_bool	ft_is_builtin(t_cmd *cmd)
{
	if (ft_strncmp(cmd->name, "cd", 3) == 0)
		return (true);
	else if (ft_strncmp(cmd->name, "echo", 5) == 0)
		return (true);
	else if (ft_strncmp(cmd->name, "env", 4) == 0)
		return (true);
	else if (ft_strncmp(cmd->name, "exit", 5) == 0)
		return (true);
	else if (ft_strncmp(cmd->name, "pwd", 4) == 0)
		return (true);
	else if (ft_strncmp(cmd->name, "export", 7) == 0)
		return (true);
	else if (ft_strncmp(cmd->name, "unset", 6) == 0)
		return (true);
	return (false);
}

int	ft_exec_builtin(t_cmd *cmd, t_list **env, int fd, t_bool is_child)
{
	if (ft_strncmp(cmd->name, "cd", 3) == 0)
		return (ft_cd(cmd->arg, env, fd));
	else if (ft_strncmp(cmd->name, "echo", 5) == 0)
		return (ft_echo(cmd->arg, fd));
	else if (ft_strncmp(cmd->name, "env", 4) == 0)
		return (ft_env(*env, fd));
	else if (ft_strncmp(cmd->name, "exit", 5) == 0)
		return (ft_exit(env, is_child));
	else if (ft_strncmp(cmd->name, "pwd", 4) == 0)
		return (ft_pwd(fd));
	else if (ft_strncmp(cmd->name, "export", 7) == 0)
		return (ft_export(cmd->arg, env, fd));
	else if (ft_strncmp(cmd->name, "unset", 6) == 0)
		return (ft_unset(cmd->arg, env));
	return (EXIT_FAILURE);
}
