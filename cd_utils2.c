/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npremont <npremont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 11:14:05 by npremont          #+#    #+#             */
/*   Updated: 2023/12/19 11:16:33 by npremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_gethome(char **en)
{
	size_t	i;
	char	*pwd;

	i = 0;
	while (en[i])
	{
		if (ft_strncmp(en[i], "HOME=", 5) == 0)
			pwd = ft_strdup(en[i] + 5);
		++i;
	}
	return (pwd);
}
