/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npremont <npremont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 11:47:22 by npremont          #+#    #+#             */
/*   Updated: 2024/03/05 13:58:36 by npremont         ###   ########.fr       */
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
			write(fd, var->name, ft_strlen(var->name));
			write(fd, "=", 1);
			write(fd, var->value, ft_strlen(var->value));
			write(fd, "\n", 1);
		}
		en = en->next;
	}
	return (EXIT_SUCCESS);
}
