/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npremont <npremont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 11:47:22 by npremont          #+#    #+#             */
/*   Updated: 2024/03/12 17:33:03 by npremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_env(t_list *en, int fd)
{
	t_globvar	*var;

	while (en)
	{
		var = en->content;
		if (var->is_secret == 0)
		{
			if (write(fd, var->name, ft_strlen(var->name)) == -1)
				return (EXIT_FAILURE);
			if (write(fd, "=", 1) == -1)
				return (EXIT_FAILURE);
			if (write(fd, var->value, ft_strlen(var->value)) == -1)
				return (EXIT_FAILURE);
			if (write(fd, "\n", 1) == -1)
				return (EXIT_FAILURE);
		}
		en = en->next;
	}
	if (write(fd, "_=/usr/bin/env\n", 16) == -1) //
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
