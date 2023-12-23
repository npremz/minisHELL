/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npremont <npremont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 13:28:29 by npremont          #+#    #+#             */
/*   Updated: 2023/12/23 19:00:29 by npremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_initshlvl(char **en)
{
	size_t		i;
	int			lvl;
	char		*new_lvl;
	char		*new_line;

	i = 0;
	while (en[i])
	{
		if (ft_strncmp(en[i], "SHLVL=", 6) == 0)
		{
			lvl = ft_atoi(en[i] + 6) + 1;
			if (lvl < 0)
				lvl = 0;
			new_lvl = ft_itoa(lvl);
			en = ft_updatevar(en, "SHLVL", new_lvl);
			return (free(new_lvl), en);
		}
		++i;
	}
	return (ft_updatevar(en, "SHLVL", "1"));
}

static char	**ft_initpwd(char **en)
{
	char	pwd[1024];

	getcwd(pwd, sizeof(pwd));
	return (ft_updatevar(en, "PWD", pwd));
}

char	**ft_envinit(char **envp)
{
	size_t	i;
	char 	**env;

	i = 0;
	while (envp[i])
		++i;
	env = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (envp[i])
	{
		env[i] = ft_strdup(envp[i]);
		++i;
	}
	env[i] = NULL;
	env = ft_initpwd(env);
	env = ft_initshlvl(env);
	return (env);
}
