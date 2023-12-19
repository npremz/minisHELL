/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npremont <npremont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 10:30:32 by npremont          #+#    #+#             */
/*   Updated: 2023/12/19 17:18:05 by npremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_gethome(char **en)
{
	size_t	i;
	char	*home;

	i = 0;
	home = NULL;
	while (en[i])
	{
		if (ft_strncmp(en[i], "HOME=", 5) == 0)
			home = ft_strdup(en[i] + 5);
		++i;
	}
	if (!home)
		home = getenv("HOME");
	return (home);
}

char	*ft_get_oldpwd(char **en)
{
	size_t	i;
	char	*home;

	i = 0;
	home = NULL;
	while (en[i])
	{
		if (ft_strncmp(en[i], "OLDPWD=", 7) == 0)
			home = ft_strdup(en[i] + 7);
		++i;
	}
	return (home);
}

