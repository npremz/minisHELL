/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 14:30:36 by lethomas          #+#    #+#             */
/*   Updated: 2024/03/13 17:07:02 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_set_pipe_fd(int *fd_pipe_in_out[2], int fd_in_out[2])
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

static int	ft_open_redirection_in(t_cmd *cmd, char **error_arg, int *fd_in,
	t_list **env)
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
			if (ft_here_doc_env(fd_in, cmd->in[i], env))
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

int	ft_open_redirection(t_cmd *cmd, char **error_arg, int *fd_in_out,
	t_list **env)
{
	int		fd;

	if (ft_open_redirection_in(cmd, error_arg, &fd, env))
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
