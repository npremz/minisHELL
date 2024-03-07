/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection_here_doc.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 22:21:29 by lethomas          #+#    #+#             */
/*   Updated: 2024/03/07 14:13:17 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
