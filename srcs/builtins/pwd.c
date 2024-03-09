/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:29:19 by npremont          #+#    #+#             */
/*   Updated: 2024/03/09 12:44:15 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd(int fd)
{
	char	cwd[1024];

	if (getcwd(cwd, 1024))
	{
		write(fd, cwd, ft_strlen(cwd));
		write (1, "\n", 1);
		return (EXIT_SUCCESS);
	}
	else
		return (EXIT_FAILURE);
}
