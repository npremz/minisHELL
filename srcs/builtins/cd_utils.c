/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npremont <npremont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:28:09 by npremont          #+#    #+#             */
/*   Updated: 2024/03/14 18:49:41 by npremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_init_gvar(t_globvar **var, char *name, char *value)
{
	(*var)->name = ft_strdup(name);
	if (!(*var)->name)
		return (free((*var)), EXIT_FAILURE);
	(*var)->value = ft_strdup(value);
	if (!(*var)->value)
		return (free_globvar((*var)), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	export_swap(t_globvar *tmp, t_globvar *var, int type)
{
	free(tmp->value);
	tmp->value = var->value;
	free(var->name);
	if (type == 2)
		free(var);
}
