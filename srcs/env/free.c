/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npremont <npremont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:08:18 by npremont          #+#    #+#             */
/*   Updated: 2024/03/05 11:34:17 by npremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_globvar(t_globvar *ptr)
{
	if ((ptr)->name)
		ft_free((void **)&((ptr)->name));
	if ((ptr)->value)
		ft_free((void **)&((ptr)->value));
	if ((ptr))
		ft_free((void **)&ptr);
}

void	ft_envclear(t_list **lst, void (*del)(t_globvar *))
{
	t_list	*temp;

	while (*lst != NULL)
	{
		(*del)((*lst)->content);
		temp = (*lst)->next;
		free(*lst);
		*lst = temp;
	}
}
