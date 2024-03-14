/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_launch_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 09:45:52 by lethomas          #+#    #+#             */
/*   Updated: 2024/03/14 18:09:44 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_close_heredoc_fd(t_cmd *cmd)
{
	int		i;
	t_bool	is_quoted;

	i = 0;
	if (cmd->in != NULL)
	{
		while (cmd->in[i] != NULL)
		{
			if (cmd->type_in[i] == redirection_here_doc)
			{
				is_quoted = false;
				if (cmd->in[i][0] == '\'')
					is_quoted = true;
				if (close(ft_atoi(cmd->in[i] + (is_quoted == true), 0)))
					return (EXIT_FAILURE);
			}
			i++;
		}
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
