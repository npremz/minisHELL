/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npremont <npremont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 14:30:36 by lethomas          #+#    #+#             */
/*   Updated: 2024/03/13 11:47:47 by npremont         ###   ########.fr       */
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

static int	ft_write_env_value(int new_fd, t_list **env, char *str,
	int *cursor_pos)
{
	char	*env_name;
	char	*env_value;
	
	if (ft_get_env_name(str + *cursor_pos, &env_name))
		return (EXIT_FAILURE);
	env_value = ft_get_gvar_value(env_name + 1, *env);
	if (env_value != NULL)
		if (write(new_fd, env_value, ft_strlen(env_value)) == -1)
			return (EXIT_FAILURE);
	*cursor_pos += ft_strlen(env_name);
	free(env_name);
	return (EXIT_SUCCESS);
}

static int	ft_fill_new_pipe(int new_fd, int old_fd, t_list **env)
{
	char	*str;
	int		cursor_pos;

	str = get_next_line(old_fd);
	while (str != NULL)
	{
		cursor_pos = 0;
		while (str[cursor_pos] != '\0')
		{
			if (str[cursor_pos] != '$')
			{
				if (write(new_fd, str + cursor_pos, 1) == -1)
					return (EXIT_FAILURE);
				cursor_pos++;
			}
			else
				if (ft_write_env_value(new_fd, env, str, &cursor_pos))
					return (EXIT_FAILURE);
		}
		free(str);
		str = get_next_line(old_fd);
	}
	return (EXIT_SUCCESS);
}

static int	ft_here_doc_env(int *fd, char *char_fd, t_list **env)
{
	t_bool	is_quoted;
	int		new_fd[2];

	is_quoted = false;
	if (char_fd[0] == '\'')
		is_quoted = true;
	*fd = ft_atoi(char_fd + (is_quoted == true), 0);
	if (is_quoted == false)
	{
		if (pipe(new_fd) == -1)
			return (EXIT_FAILURE);
		if (ft_fill_new_pipe(new_fd[1], *fd, env))
			return (EXIT_FAILURE);
		if (close(*fd))
			return (EXIT_FAILURE);
		*fd = new_fd[0];
		if (close(new_fd[1]))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	ft_open_redirection_in(t_cmd *cmd, char **error_arg, int *fd_in, t_list **env)
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

int	ft_open_redirection(t_cmd *cmd, char **error_arg, int *fd_in_out, t_list **env)
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
