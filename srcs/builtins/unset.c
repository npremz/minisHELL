/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npremont <npremont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 17:08:09 by npremont          #+#    #+#             */
/*   Updated: 2024/03/05 11:26:50 by npremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_list	*free_node(t_list *node)
{
	t_list	*next;

	next = node->next;
	free_globvar(node->content);
	node->next = NULL;
	free(node);
	return (next);
}

int	ft_unset(char **args, t_list **en)
{
	t_globvar	*var;
	t_list		*en_cp;

	if (!args[1])
		return (EXIT_SUCCESS);
	var = (*en)->content;
	if (ft_strncmp(args[1], var->name, ft_strlen(var->name)) == 0)
	{
		*en = free_node(*en);
		return (EXIT_SUCCESS);
	}
	en_cp = *en;
	while (en_cp && en_cp->next)
	{
		var = en_cp->next->content;
		if (ft_strncmp(args[1], var->name, ft_strlen(var->name)) == 0)
		{
			en_cp->next = free_node(en_cp->next);
			return (EXIT_SUCCESS);
		}
		en_cp = en_cp->next;
	}
	return (EXIT_SUCCESS);
}
