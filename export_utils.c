/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npremont <npremont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 16:03:24 by npremont          #+#    #+#             */
/*   Updated: 2023/12/23 18:03:02 by npremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_sort_tab(char **en)
{
	size_t	i;
	char	*tmp;
	char	**en_dup;

	i = 0;
	while (en[i])
		++i;
	en_dup = malloc((i + 1) * sizeof(char *));
	ft_tabdup(en_dup, en);
	i = 1;
	while (en_dup[i])
	{
		if (ft_strncmp(en_dup[i], en_dup[i - 1], ft_strlen(en_dup[i - 1])) < 0)
		{
			tmp = en_dup[i];
			en_dup[i] = en_dup[i - 1];
			en_dup[i - 1] = tmp;
			i = 0;
		}
		++i;
	}
	return (en_dup);
}

void	ft_display_exp(char **en)
{
	size_t	i;
	size_t	j;
	char	**sorted;

	sorted = ft_sort_tab(en);
	i = 0;
	while (sorted[i])
	{
		j = 0;
		write(1, "declare -x ", 12);
		while (sorted[i][j] != '=')
			write(1, &sorted[i][j++], 1);
		write(1, &sorted[i][j++], 1);
		write(1, "\"", 2);
		while (sorted[i][j] != '\0')
			write(1, &sorted[i][j++], 1);
		write(1, "\"\n", 3);
		++i;
	}
	ft_free_split(sorted);
}

int	ft_gettype(char *arg)
{
	size_t	i;

	i = 0;
	if (ft_isalpha(arg[i]) == 0 && arg[i] != '_')
		return (0);
	++i;
	while (arg[i] != '=' && arg[i] != '\0')
	{
		if (arg[i] == '+' && arg[i + 1] == '=')
			return (1);
		if (ft_isalnum(arg[i]) == 0 && arg[i] != '_')
			return (0);
		++i;
	}
	if (arg[i] == '=')
		return (2);
	else
		return (3);
}

char	**ft_updatevar_exp(char **en, char *arg)
{
	size_t	i;
	size_t	j;
	char	*new_line;

	i = 0;
	while (en[i])
	{
		j = 0;
		while (en[i][j] == arg[j] && en[i][j] != '=' && arg[j] != '+')
			++j;
		if (en[i][j] == '=' && arg[j] == '+')
		{
			new_line = ft_strjoin(en[i], arg + j + 2);
			ft_free(en[i]);
			en[i] = new_line;
			return (en);
		}
		++i;
	}
	j = 0;
	while (arg[j] != '+')
		++j;
	arg[j] = '\0';
	new_line = ft_strjoin(arg, arg + j + 1);
	return (ft_addvar(en, new_line));
}
