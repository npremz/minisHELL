/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 00:19:09 by lethomas          #+#    #+#             */
/*   Updated: 2024/03/14 17:24:03 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_basename(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	while (str[i] != '/' && i != 0)
		i--;
	if (str[i] == '/')
		return (&str[++i]);
	return (str);
}

static char	*ft_strerror(int errnum)
{
	if (errnum < 200)
		return (strerror(errnum));
	else if (errnum == 200)
		return ("command not found");
	else if (errnum == 201)
		return ("ambiguous redirect");
	else if (errnum == 202)
		return ("is a directory");
	return ("unknowed code error");
}

int	ft_display_error(char *arg_error)
{
	if (errno == 0)
		return (EXIT_SUCCESS);
	if (ft_putstr_fd("minishell", STDERR_FILENO))
		return (EXIT_FAILURE);
	if (arg_error != NULL)
	{
		if (ft_putstr_fd(": ", STDERR_FILENO))
			return (EXIT_FAILURE);
		if (ft_putstr_fd(arg_error, STDERR_FILENO))
			return (EXIT_FAILURE);
	}
	if (ft_putstr_fd(": ", STDERR_FILENO))
		return (EXIT_FAILURE);
	if (ft_putstr_fd(ft_strerror(errno), STDERR_FILENO))
		return (EXIT_FAILURE);
	if (ft_putstr_fd("\n", STDERR_FILENO))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	ft_get_exit_code(int status)
{
	if (errno == 200)
		return (127);
	else
		return (status);
}

int	ft_exit_child(t_cmd *cmd, int *fd_pipe_tab[2], int status,
	char *error_arg)
{
	free(fd_pipe_tab[0]);
	free(fd_pipe_tab[1]);
	ft_free_cmd_tree(cmd->root);
	if (status == EXIT_FAILURE)
		ft_display_error(error_arg);
	free(error_arg);
	exit(ft_get_exit_code(status));
}
