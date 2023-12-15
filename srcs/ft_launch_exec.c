/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_launch_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 19:38:40 by lethomas          #+#    #+#             */
/*   Updated: 2023/12/15 01:05:36 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing_exec.h"

static int	ft_dup_pipe(int *fd_pipe_in, int *fd_pipe_out)
{
	if (fd_pipe_in != NULL)
	{
		if (close(fd_pipe_in[1]))
			return (EXIT_FAILURE);
		if (dup2(fd_pipe_in[0], STDIN_FILENO) == -1)
			return (EXIT_FAILURE);
		if (close(fd_pipe_in[0]))
			return (EXIT_FAILURE);
	}
	if (fd_pipe_out != NULL)
	{
		if (close(fd_pipe_out[0]))
			return (EXIT_FAILURE);
		if (dup2(fd_pipe_out[1], STDOUT_FILENO) == -1)
			return (EXIT_FAILURE);
		if (close(fd_pipe_out[1]))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	ft_dup_redirection_in(t_cmd *cmd, char **error_arg)
{
	int	i;
	int	fd_in;

	i = 0;
	if (cmd->in[0] == NULL)
		return (EXIT_SUCCESS);
	while (cmd->in[i] != NULL)
	{
		if (cmd->type_in == redirection_in)
		{
			fd_in = open(cmd->in[i], O_RDONLY);
			if (fd_in < 0)
				return (*error_arg = ft_strdup(cmd->in[i]), EXIT_FAILURE);
			if (cmd->in[i + 1] != NULL)
				if (close(fd_in))
					return (*error_arg = ft_strdup(cmd->in[i]), EXIT_FAILURE);
		}
		i++;
	}
	if (dup2(fd_in, STDIN_FILENO) == -1)
		return (EXIT_FAILURE);
	if (close(fd_in))
		return (*error_arg = ft_strdup(cmd->in[i]), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
//gerer le heredoc

static int	ft_dup_redirection_out(t_cmd *cmd, char **error_arg)
{
	int	i;
	int	fd_out;

	i = 0;
	if (cmd->out[0] == NULL)
		return (EXIT_SUCCESS);
	while (cmd->out[i] != NULL)
	{
		if (cmd->type_out == redirection_out)
			fd_out = open(cmd->out[i],
					O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
		if (cmd->type_out == redirection_append)
			fd_out = open(cmd->out[i],
					O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
		if (fd_out < 0)
			return (*error_arg = ft_strdup(cmd->out[i]), EXIT_FAILURE);
		if (cmd->out[i++ + 1] != NULL)
			if (close(fd_out))
				return (*error_arg = ft_strdup(cmd->out[--i]), EXIT_FAILURE);
	}
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		return (EXIT_FAILURE);
	if (close(fd_out))
		return (*error_arg = ft_strdup(cmd->out[--i]), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static void	ft_dup_exec(t_cmd *cmd, int *fd_pipe_in, int *fd_pipe_out)
{
	char	*error_arg;
	int		*fd_pipe_tab[2];

	error_arg = NULL;
	fd_pipe_tab[0] = fd_pipe_in;
	fd_pipe_tab[1] = fd_pipe_out;
	if (ft_dup_pipe(fd_pipe_in, fd_pipe_out))
		ft_exit_child(cmd, fd_pipe_tab, EXIT_FAILURE, error_arg);
	if (ft_dup_redirection_in(cmd, &error_arg))
		ft_exit_child(cmd, fd_pipe_tab, EXIT_FAILURE, error_arg);
	if (ft_dup_redirection_out(cmd, &error_arg))
		ft_exit_child(cmd, fd_pipe_tab, EXIT_FAILURE, error_arg);
	if (ft_exec(cmd, &error_arg))
		ft_exit_child(cmd, fd_pipe_tab, EXIT_FAILURE, error_arg);
	ft_exit_child(cmd, fd_pipe_tab, EXIT_SUCCESS, error_arg);
}
//free cmd_tree avant exit

int	ft_launch_exec(t_btree *cmd_tree, t_cmd_type operator_out, int **fd_pipe_in,
	int *pid_child_tab)
{
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
	pid_child_tab++;
	while (*pid_child_tab != 0)
		pid_child_tab++;
	*pid_child_tab = fork();
	if (*pid_child_tab < 0)
		return (EXIT_FAILURE);
	if (*pid_child_tab == 0)
		ft_dup_exec((t_cmd *)cmd_tree->item, *fd_pipe_in, fd_pipe_out);
	if (*fd_pipe_in != NULL)
		if (close((*fd_pipe_in)[0]) || close((*fd_pipe_in)[1]))
			return (EXIT_FAILURE);
	free(*fd_pipe_in);
	*fd_pipe_in = fd_pipe_out;
	return (EXIT_SUCCESS);
}
