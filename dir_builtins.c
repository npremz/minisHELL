/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npremont <npremont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 10:39:42 by npremont          #+#    #+#             */
/*   Updated: 2023/12/19 18:56:02 by npremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(void)
{
	char	cwd[1024];

	getcwd(cwd, sizeof(cwd));
	ft_printf("%s\n", cwd);
}

void	ft_cd(char **args, char **en)
{
	char	*pwd;
	char	old_pwd[1024];

	pwd = args[1];
	getcwd(old_pwd, sizeof(old_pwd));
	if (!args[1])
		pwd = ft_gethome(en);
	else if (args[1][0] == '-' && !args[1][1])
	{
		pwd = ft_get_oldpwd(en);
		if (!pwd)
		{
			write(2, "OLDPWD not set\n", 16);
			perror("cd");
		}
		if (access(pwd, F_OK) == 0)
			ft_printf("%s", pwd);
	}
	else if (pwd[0] == '~')
		pwd = ft_tilde(en, pwd);
	if (chdir(pwd) == -1)
		perror("cd");
	else 
		ft_updatepwd(en, pwd, old_pwd);
}
