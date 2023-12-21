/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npremont <npremont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 10:30:32 by npremont          #+#    #+#             */
/*   Updated: 2023/12/21 11:54:02 by npremont         ###   ########.fr       */
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

char	*ft_tilde(char **env, char *pwd)
{
	char	*new;
	char	*home;

	home = ft_gethome(env);
	if (!home)
		return (NULL);
	new = ft_strjoin(home, pwd + 1);
	free(home);
	free(pwd);
	return (new);
}

char	*ft_getvarline(char **en, char *varname)
{
	size_t	i;

	i = 0;
	while (en[i])
	{
		if (ft_strncmp(en[i], varname, ft_strlen(varname)) == 0)
			return (en[i]);
		++i;
	}
	return (NULL);
}

char	**ft_updatevar(char **en, char *name, char *value)
{
	size_t	i;
	char	*varname;
	char	*varline;

	varname = ft_strjoin(name, "=");
	varline = ft_strjoin(varname, value);
	i = 0;
	while (en[i])
	{
		if (ft_strncmp(en[i], varname, ft_strlen(varname)) == 0)
		{
			ft_free(en[i]);
			en[i] = varline;
			return (free(varname), en);
		}
		++i;
	}
	free(varname);
	return (ft_addvar(en, varline));
}
