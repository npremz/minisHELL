/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npremont <npremont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 13:28:29 by npremont          #+#    #+#             */
/*   Updated: 2023/12/18 18:36:30 by npremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_envinit(char **envp, char **env)
{
	size_t	i;

	i = 0;
	while (envp[i])
		++i;
	env = malloc((sizeof(char *) * i) + 1);
	i = 0;
	while (envp[i])
	{
		env[i] = ft_strdup(envp[i]);
		++i;
	}
	env[i] = NULL;
	return (env);
}
