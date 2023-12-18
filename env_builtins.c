/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npremont <npremont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 15:19:27 by npremont          #+#    #+#             */
/*   Updated: 2023/12/18 18:42:47 by npremont         ###   ########.fr       */
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
