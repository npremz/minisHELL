/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npremont <npremont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 15:19:27 by npremont          #+#    #+#             */
/*   Updated: 2023/12/20 23:56:26 by npremont         ###   ########.fr       */
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
