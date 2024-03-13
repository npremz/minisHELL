/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_last_child.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:19:10 by lethomas          #+#    #+#             */
/*   Updated: 2024/03/13 17:24:22 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_bool	ft_is_last_child(pid_t *pid_child_tab, int j)
{
	int	i;

	i = 0;
	while (pid_child_tab[j + ++i] != -42)
		if (pid_child_tab[j + i] != 0)
			return (false);
	return (true);
}
