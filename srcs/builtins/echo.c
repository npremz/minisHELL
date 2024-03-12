/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npremont <npremont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 13:07:20 by npremont          #+#    #+#             */
/*   Updated: 2024/03/12 13:22:01 by npremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_isnot_nl(char *str)
{
	if (*str == '-')
		++str;
	else
		return (0);
	while (*str && *str == 'n')
		++str;
	if (!*str && *(str - 1) == 'n')
		return (1);
	return (0);
}

int	ft_echo(char **args, int fd)
{
	size_t	i;
	int		nl;

	i = 1;
	nl = 1;
	if (args[i])
	{
		while (args[i] && ft_isnot_nl(args[i]))
			++i;
		if (i > 1)
			nl = 0;
		while (args[i])
		{
			if (write(fd, args[i], ft_strlen(args[i])) == -1)
				return (EXIT_FAILURE);
			++i;
			if (args[i])
				if (write(fd, " ", 1) == -1)
					return (EXIT_FAILURE);
		}
	}
	if (nl)
		if (write(fd, "\n", 1) == -1)
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
