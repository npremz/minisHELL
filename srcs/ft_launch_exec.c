/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_launch_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 09:45:52 by lethomas          #+#    #+#             */
/*   Updated: 2024/03/09 12:49:35 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_is_an_ambiguous_red(char *red_name)
{
	char	*pt;

	pt = ft_strnstr(red_name, ":ambiguous_redirect", ft_strlen(red_name));
	if (pt != NULL && pt[ft_strlen(":ambiguous_redirect")] == '\0')
	{
		pt[0] = '\0';
		return (true);
	}
	return (false);
}

static int	ft_open_redirection_in(t_cmd *cmd, char **error_arg, int *fd_in)
{
	int	i;

	i = 0;
	*fd_in = -1;
	if (cmd->in[0] == NULL)
		return (EXIT_SUCCESS);
	while (cmd->in[i] != NULL)
	{
		if (ft_is_an_ambiguous_red(cmd->in[i]) == true)
			return (errno = 201, *error_arg = ft_strdup(cmd->in[i]),
				EXIT_FAILURE);
		if (cmd->type_in[i] == redirection_in)
		{
			*fd_in = open(cmd->in[i], O_RDONLY);
			if (*fd_in < 0)
				return (*error_arg = ft_strdup(cmd->in[i]), EXIT_FAILURE);
		}
		else
			if (ft_redirection_here_doc(fd_in, cmd->in[i]))
				return (EXIT_FAILURE);
		if (cmd->in[i + 1] != NULL && close(*fd_in))
			return (*error_arg = ft_strdup(cmd->in[i]), EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

static int	ft_open_redirection_out(t_cmd *cmd, char **error_arg, int *fd_out)
{
	int	i;

	i = 0;
	*fd_out = -1;
	if (cmd->out[0] == NULL)
		return (EXIT_SUCCESS);
	while (cmd->out[i] != NULL)
	{
		if (ft_is_an_ambiguous_red(cmd->out[i]) == true)
			return (errno = 201, *error_arg = ft_strdup(cmd->out[i]),
				EXIT_FAILURE);
		if (cmd->type_out[i] == redirection_out)
			*fd_out = open(cmd->out[i],
					O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
		if (cmd->type_out[i] == redirection_append)
			*fd_out = open(cmd->out[i],
					O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
		if (*fd_out < 0)
			return (*error_arg = ft_strdup(cmd->out[i]), EXIT_FAILURE);
		if (cmd->out[i + 1] != NULL)
			if (close(*fd_out))
				return (*error_arg = ft_strdup(cmd->out[i]), EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

static int	ft_open_redirection(t_cmd *cmd, char **error_arg, int *fd_in_out)
{
	int		fd;

	if (ft_open_redirection_in(cmd, error_arg, &fd))
		return (EXIT_FAILURE);
	if (fd != -1)
	{
		if (fd_in_out[0] != -1 && close(fd_in_out[0]))
			return (EXIT_FAILURE);
		fd_in_out[0] = fd;
	}
	if (ft_open_redirection_out(cmd, error_arg, &fd))
		return (EXIT_FAILURE);
	if (fd != -1)
	{
		if (fd_in_out[1] != -1 && close(fd_in_out[1]))
			return (EXIT_FAILURE);
		fd_in_out[1] = fd;
	}
	return (EXIT_SUCCESS);
}

static int	ft_set_pipe_fd(int *fd_pipe_in_out[2], int fd_in_out[2])
{
	if (fd_pipe_in_out[0] != NULL)
	{
		if (close(fd_pipe_in_out[0][1]))
			return (EXIT_FAILURE);
		fd_in_out[0] = fd_pipe_in_out[0][0];
	}
	if (fd_pipe_in_out[1] != NULL)
	{
		if (close(fd_pipe_in_out[1][0]))
			return (EXIT_FAILURE);
		fd_in_out[1] = fd_pipe_in_out[1][1];
	}
	return (EXIT_SUCCESS);
}

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
	if (ft_open_redirection(cmd, &error_arg, fd_in_out))
		ft_exit_child(cmd, fd_pipe_in_out, EXIT_FAILURE, error_arg);
	if (ft_dup(fd_in_out))
		ft_exit_child(cmd, fd_pipe_in_out, EXIT_FAILURE, error_arg);
	if (cmd->name == NULL)
		ft_exit_child(cmd, fd_pipe_in_out, EXIT_SUCCESS, error_arg);
	if (ft_exec(cmd, &error_arg, env))
		ft_exit_child(cmd, fd_pipe_in_out, EXIT_FAILURE, error_arg);
	ft_exit_child(cmd, fd_pipe_in_out, EXIT_SUCCESS, error_arg);
}

static int	ft_launch_builtout(t_cmd *cmd, int **fd_pipe_in_out,
	int *pid_child_tab, t_list **env)
{
	pid_child_tab++;
	while (*pid_child_tab != 0)
		pid_child_tab++;
	*pid_child_tab = fork();
	if (*pid_child_tab < 0)
		return (EXIT_FAILURE);
	if (*pid_child_tab == 0)
		ft_open_dup_exec(cmd, fd_pipe_in_out, env);
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

static int	ft_open_exec(t_cmd *cmd, int *fd_pipe_in_out[2], t_list **env,
	t_bool is_child, int *return_value)
{
	char	*error_arg;
	int		fd_in_out[2];

	error_arg = NULL;
	fd_in_out[0] = 0;
	fd_in_out[1] = 1;
	if (ft_set_pipe_fd(fd_pipe_in_out, fd_in_out))
		return (EXIT_FAILURE);
	if (ft_open_redirection(cmd, &error_arg, fd_in_out))
		return (EXIT_FAILURE);
	if (fd_in_out[0] != 0 && close(fd_in_out[0]))
		return (EXIT_FAILURE);
	*return_value = ft_exec_builtin(cmd, env, fd_in_out[1], is_child);
	if (fd_in_out[1] != 1 && close(fd_in_out[1]))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	ft_launch_builtin(t_cmd *cmd, int **fd_pipe_in_out,
	int *pid_child_tab, t_list **env)
{
	int	i;

	i = 1;
	while (pid_child_tab[i] != 0)
		i++;
	if (fd_pipe_in_out[0] != NULL || fd_pipe_in_out[1] != NULL)
	{
		pid_child_tab[i] = fork();
		if (pid_child_tab[i] < 0)
			return (EXIT_FAILURE);
		if (pid_child_tab[i] == 0)
		{
			if (ft_open_exec(cmd, fd_pipe_in_out, env, true, pid_child_tab))
				exit(EXIT_FAILURE);
			exit(*pid_child_tab);
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
	}
	else
	{
		pid_child_tab[i] = -45;
		if (ft_open_exec(cmd, fd_pipe_in_out, env, false, pid_child_tab))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	ft_launch_exec(t_cmd *cmd, int **fd_pipe_in_out,
	int *pid_child_tab, t_list **env)
{
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
