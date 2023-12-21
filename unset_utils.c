/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npremont <npremont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 11:58:59 by npremont          #+#    #+#             */
/*   Updated: 2023/12/21 12:01:30 by npremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_getline_pos(char **en, char *arg)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (en[i])
	{
		j = 0;
		while (en[i][j] == arg[j] && en[i][j] != '=' && arg[j] != '=')
			++j;
		if (en[i][j] == '=' && arg[j] == '=')
			return (i);
		++i;
	}
	return (-1);
}
