/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npremont <npremont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 15:19:27 by npremont          #+#    #+#             */
/*   Updated: 2023/12/23 16:48:18 by npremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(char **env_list)
{
	size_t	i;

	i = 0;
	if (!*env_list)
		return ;
	while (env_list[i])
	{
		ft_printf("%s\n", env_list[i]);
		++i;
	}
}

void	ft_export(char **args, char ***en)
{
	size_t	i;
	int		type;

	i = 1;
	if (!args[1])
	{
		ft_display_exp(*en);
		return ;
	}
	while (args[i])
	{
		type = ft_gettype(args[i]);
		if (type == 1)
			*en = ft_updatevar_exp(*en, args[i]);
		else if (type == 2)
			*en = ft_addvar(*en, args[i]);
		++i;
	}
}

void	ft_unset(char **args, char ***en)
{
	size_t	i;
	int		line_pos;

	i = 0;
	if (!args[1])
		return ;
	while (args[++i])
	{
		line_pos = ft_getline_pos(*en, args[i]);
		printf("%d\n", line_pos);
		if (line_pos == -1)
			continue ;
		*en = ft_rmvar(*en, line_pos);
	}
}

void	ft_echo(char **args)
{
	size_t	i;
	int		nl;

	i = 1;
	nl = 1;
	if (args[i])
	{
		while (args[i] && ft_isnot_nl(args[i]))
			++i;
		if (i > 1)
			nl = 0;
		while (args[i])
		{
			write(1, args[i], ft_strlen(args[i]));
			++i;
			if (args[i])
				write(1, " ", 1);
		}
	}
	if (nl)
		write(1, "\n", 1);
}
