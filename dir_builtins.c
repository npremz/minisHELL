/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npremont <npremont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 10:39:42 by npremont          #+#    #+#             */
/*   Updated: 2023/12/18 18:47:39 by npremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(void)
{
	char	cwd[1024];

	getcwd(cwd, sizeof(cwd));
	ft_printf("%s\n", cwd);
}

void	ft_cd(char *line, char **en)
{
	
}
