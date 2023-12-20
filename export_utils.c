/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npremont <npremont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 16:03:24 by npremont          #+#    #+#             */
/*   Updated: 2023/12/20 18:18:26 by npremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_sort_tab(char **en)
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
	ft_free_split(en_dup);
}

void	ft_display_exp(char **en)
{
	size_t	i;
	size_t	j;

	ft_sort_tab(en);
	i = 0;
	while (en[i])
	{
		j = 0;
		write(1, "declare -x ", 12);
		while (en[i][j] != '=')
			write(1, &en[i][j++], 1);
		write(1, &en[i][j++], 1);
		write(1, "\"", 2);
		while (en[i][j] != '\0')
			write(1, &en[i][j++], 1);
		write(1, "\"\n", 3);
		++i;
	}
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
