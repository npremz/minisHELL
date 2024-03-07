/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npremont <npremont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:29:19 by npremont          #+#    #+#             */
/*   Updated: 2024/03/05 14:02:41 by npremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd(int fd)
{
	char	cwd[1024];

	if (getcwd(cwd, 1024))
	{
		write(fd, cwd, ft_strlen(cwd));
		return (EXIT_SUCCESS);
	}
	else
		return (EXIT_FAILURE);
}
