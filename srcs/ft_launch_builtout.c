/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_launch_builtout.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 14:35:10 by lethomas          #+#    #+#             */
/*   Updated: 2024/03/13 12:11:34 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_dup(int fd_in_out[2])
{
	if (fd_in_out[0] != -1)
	{
		if (dup2(fd_in_out[0], STDIN_FILENO) == -1)
			return (EXIT_FAILURE);
		if (close(fd_in_out[0]))
			return (EXIT_FAILURE);
	}
	if (fd_in_out[1] != -1)
	{
		if (dup2(fd_in_out[1], STDOUT_FILENO) == -1)
			return (EXIT_FAILURE);
		if (close(fd_in_out[1]))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static void	ft_open_dup_exec(t_cmd *cmd, int *fd_pipe_in_out[2], t_list **env)
{
	char	*error_arg;
	int		fd_in_out[2];

	error_arg = NULL;
	fd_in_out[0] = -1;
	fd_in_out[1] = -1;
	if (ft_set_pipe_fd(fd_pipe_in_out, fd_in_out))
		ft_exit_child(cmd, fd_pipe_in_out, EXIT_FAILURE, error_arg);
	if (ft_open_redirection(cmd, &error_arg, fd_in_out, env))
		ft_exit_child(cmd, fd_pipe_in_out, EXIT_FAILURE, error_arg);
	if (ft_dup(fd_in_out))
		ft_exit_child(cmd, fd_pipe_in_out, EXIT_FAILURE, error_arg);
	if (cmd->name == NULL)
		ft_exit_child(cmd, fd_pipe_in_out, EXIT_SUCCESS, error_arg);
	if (ft_exec(cmd, &error_arg, env))
		ft_exit_child(cmd, fd_pipe_in_out, EXIT_FAILURE, error_arg);
	ft_exit_child(cmd, fd_pipe_in_out, EXIT_SUCCESS, error_arg);
}

int	ft_launch_builtout(t_cmd *cmd, int **fd_pipe_in_out,
	int *pid_child_tab, t_list **env)
{
	pid_child_tab++;
	while (*pid_child_tab != 0)
		pid_child_tab++;
	*pid_child_tab = fork();
	if (*pid_child_tab < 0)
		return (EXIT_FAILURE);
	if (*pid_child_tab == 0)
		signal(SIGQUIT, SIG_IGN);
	if (*pid_child_tab == 0)
		ft_open_dup_exec(cmd, fd_pipe_in_out, env);
	else
	{
		if (ft_close_heredoc_fd(cmd))
			return (EXIT_FAILURE);
		if (fd_pipe_in_out[0] != NULL)
			if (close((fd_pipe_in_out)[0][0])
				|| close((fd_pipe_in_out)[0][1]))
				return (EXIT_FAILURE);
		free(fd_pipe_in_out[0]);
		fd_pipe_in_out[0] = fd_pipe_in_out[1];
		fd_pipe_in_out[1] = NULL;
	}
	return (EXIT_SUCCESS);
}
