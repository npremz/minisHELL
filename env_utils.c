/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npremont <npremont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 11:14:05 by npremont          #+#    #+#             */
/*   Updated: 2023/12/23 16:49:27 by npremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_tabdup(char **dst, char **src)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		dst[i] = ft_strdup(src[i]);
		++i;
	}
	dst[i] = NULL;
}

char	**ft_addvar(char **en, char *var)
{
	size_t	i;
	char	**tmp;

	i = 0;
	while (en[i])
		++i;
	tmp = malloc(sizeof(char *) * (i + 2));
	ft_tabdup(tmp, en);
	tmp[i] = var;
	tmp[i + 1] = NULL;
	ft_free_split(en);
	return (tmp);
}

char	**ft_rmvar(char **en, int pos)
{
	size_t	i;
	size_t	j;
	char	**tmp;

	i = 0;
	while (en[i])
		++i;
	tmp = malloc(sizeof(char *) * i);
	i = 0;
	j = 0;
	while (en[i])
	{
		if (i == pos)
			++i;
		if (en[i])
			tmp[j++] = ft_strdup(en[i++]);
	}
	tmp[j] = NULL;
	ft_free_split(en);
	return (tmp);
}

int	ft_isnot_nl(char *str)
{
	if (*str == '-')
		++str;
	else
		return (0);
	while (*str && *str == 'n')
		++str;
	if (!*str && *(str - 1) == 'n')
		return (1);
	return (0);
}
