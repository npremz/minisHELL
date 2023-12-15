/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 00:19:09 by lethomas          #+#    #+#             */
/*   Updated: 2023/12/15 01:05:36 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing_exec.h"

// static int	ft_ind_basename(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 		i++;
// 	while (str[i] != '/' && i != 0)
// 		i--;
// 	if (str[i] == '/')
// 		return (++i);
// 	return (i);
// }

static char	*ft_strerror(int errnum)
{
	if (errnum < 200)
		return (strerror(errnum));
	else if (errnum == 200)
		return ("command not found");
	return ("unknowed code error");
}

static int	ft_display_error(char *arg_error)
{
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
