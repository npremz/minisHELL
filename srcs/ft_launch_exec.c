/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_launch_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npremont <npremont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 09:45:52 by lethomas          #+#    #+#             */
/*   Updated: 2024/03/12 12:00:21 by npremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_open_exec(t_cmd *cmd, int *fd_pipe_in_out[2], t_list **env,
	char **error_arg)
{
	int		fd_in_out[2];
	t_bool	is_child;
	int		return_value;

	fd_in_out[0] = 0;
	fd_in_out[1] = 1;
	if (fd_pipe_in_out[0] != NULL || fd_pipe_in_out[1] != NULL)
		is_child = true;
	if (ft_set_pipe_fd(fd_pipe_in_out, fd_in_out))
		return (EXIT_FAILURE);
	if (ft_open_redirection(cmd, error_arg, fd_in_out))
		return (EXIT_FAILURE);
	if (fd_in_out[0] != 0 && close(fd_in_out[0]))
		return (EXIT_FAILURE);
	return_value = ft_exec_builtin(cmd, env, fd_in_out[1], is_child);
	if (fd_in_out[1] != 1 && close(fd_in_out[1]))
		return (EXIT_FAILURE);
	return (return_value);
}

static int	ft_launch_builtin_forked(t_cmd *cmd, int **fd_pipe_in_out,
	int *pid_child_tab, t_list **env)
{
	char	*error_arg;

	error_arg = NULL;
	*pid_child_tab = fork();
	if (*pid_child_tab < 0)
		return (EXIT_FAILURE);
	if (*pid_child_tab == 0)
		signal(SIGQUIT, ft_null);
	if (*pid_child_tab == 0)
	{
		if (ft_open_exec(cmd, fd_pipe_in_out, env, &error_arg))
			ft_exit_child(cmd, fd_pipe_in_out, EXIT_FAILURE, error_arg);
		ft_exit_child(cmd, fd_pipe_in_out, EXIT_SUCCESS, NULL);
	}
	else
	{
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

static int	ft_launch_builtin(t_cmd *cmd, int **fd_pipe_in_out,
	int *pid_child_tab, t_list **env)
{
	int		i;
	char	*error_arg;

	i = 1;
	error_arg = NULL;
	while (pid_child_tab[i] != 0)
		i++;
	if (fd_pipe_in_out[0] != NULL || fd_pipe_in_out[1] != NULL)
	{
		if (ft_launch_builtin_forked(cmd, fd_pipe_in_out, pid_child_tab, env))
			return (EXIT_FAILURE);
	}
	else
	{
		pid_child_tab[i] = -45;
		*pid_child_tab = ft_open_exec(cmd, fd_pipe_in_out, env, &error_arg);
		if (*pid_child_tab != EXIT_SUCCESS)
			if (ft_display_error(error_arg))
				return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	ft_launch_exec(t_cmd *cmd, int **fd_pipe_in_out,
	int *pid_child_tab, t_list **env)
{
	if (ft_set_env_calls(cmd, *env, DEBUG_MODE))
		return (EXIT_FAILURE);
	if (ft_set_wildcard_for_cmd(cmd))
		return (EXIT_FAILURE);
	if (ft_is_builtin(cmd) == false)
	{
		if (ft_launch_builtout(cmd, fd_pipe_in_out, pid_child_tab, env))
			return (EXIT_FAILURE);
	}
	else
		if (ft_launch_builtin(cmd, fd_pipe_in_out, pid_child_tab, env))
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_init_exec(t_btree *cmd_tree, t_cmd_type operator_out,
	int **fd_pipe_in, int *pid_child_tab, t_list **env)
{
	int	*fd_pipe_in_out[2];
	int	*fd_pipe_out;

	fd_pipe_out = NULL;
	if (operator_out == pipe_operator_cmd)
	{
		fd_pipe_out = (int *)malloc(2 * sizeof(int));
		if (fd_pipe_out == NULL)
			return (EXIT_FAILURE);
		if (pipe(fd_pipe_out) == -1)
			return (EXIT_FAILURE);
	}
	fd_pipe_in_out[0] = *fd_pipe_in;
	fd_pipe_in_out[1] = fd_pipe_out;
	if (ft_launch_exec((t_cmd *)cmd_tree->item, fd_pipe_in_out,
			pid_child_tab, env))
		return (EXIT_FAILURE);
	*fd_pipe_in = fd_pipe_in_out[0];
	return (EXIT_SUCCESS);
}
