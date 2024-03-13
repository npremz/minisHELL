/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection_here_doc.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 22:21:29 by lethomas          #+#    #+#             */
/*   Updated: 2024/03/13 17:07:15 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_write_env_value(int new_fd, t_list **env, char *str,
	int *cursor_pos)
{
	char	*env_name;
	char	*env_value;

	if (ft_get_env_name(str + *cursor_pos, &env_name))
		return (EXIT_FAILURE);
	if (env_name[0] == '$' && env_name[1] == '\0')
	{
		(*cursor_pos)++;
		if (write(new_fd, "$", 1) == -1)
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
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

int	ft_here_doc_env(int *fd, char *char_fd, t_list **env)
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

static int	ft_read_here_doc(char *delimiter, int fd_pipe_write)
{
	char	*buffer;

	while (true)
	{
		ft_printf(">");
		buffer = get_next_line(STDIN_FILENO);
		if (buffer == NULL)
			return (EXIT_SUCCESS);
		if ((ft_strncmp(buffer, delimiter, ft_strlen(buffer) - 1)) == 0
			&& ft_strlen(buffer) - 1 == ft_strlen(delimiter))
			break ;
		if (write(fd_pipe_write, buffer, ft_strlen(buffer)) < 0)
			return (EXIT_FAILURE);
		free(buffer);
	}
	free(buffer);
	return (EXIT_SUCCESS);
}

int	ft_redirection_here_doc(int *fd_in, char *delimiter)
{
	int		fd_pipe[2];

	if (pipe(fd_pipe))
		return (EXIT_FAILURE);
	if (ft_read_here_doc(delimiter, fd_pipe[1]))
		return (EXIT_FAILURE);
	if (close(fd_pipe[1]))
		return (EXIT_FAILURE);
	*fd_in = fd_pipe[0];
	return (EXIT_SUCCESS);
}
