/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npremont <npremont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 14:05:06 by npremont          #+#    #+#             */
/*   Updated: 2024/03/13 16:15:53 by npremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	update_env(t_list **en, char act_pwd[1024])
{
	t_globvar	*var;

	var = malloc(sizeof(t_globvar));
	if (!var)
		return (EXIT_FAILURE);
	var->name = ft_strdup("OLDPWD");
	if (!var->name)
		return (free(var), EXIT_FAILURE);
	var->value = ft_strdup(act_pwd);
	if (!var->value)
		return (free_globvar(var), EXIT_FAILURE);
	if (ft_export_var(4, en, var) == 1)
		return (free_globvar(var), EXIT_FAILURE);
	getcwd(act_pwd, 1024);
	var->name = ft_strdup("PWD");
	if (!var->name)
		return (free(var), EXIT_FAILURE);
	var->value = ft_strdup(act_pwd);
	if (!var->value)
		return (free_globvar(var), EXIT_FAILURE);
	if (ft_export_var(4, en, var) == 1)
		return (free_globvar(var), EXIT_FAILURE);
	free(var);
	return (EXIT_SUCCESS);
}

char	*ft_get_gvar_value(char *str, t_list *en)
{
	t_globvar	*var;

	var = NULL;
	while (en)
	{
		var = en->content;
		if (ft_strncmp(str, var->name, ft_strlen(str) + 1) == 0) //
			return (var->value);
		en = en->next;
	}
	return (NULL);
}

int	ft_go_to_path(char *str, t_list **en, char act_pwd[1024], int fd)
{
	char	*path;

	path = ft_get_gvar_value(str, *en);
	if (!path)
		return (print_error("cd: « "), print_error(str),
			print_error(" » not set.\n"), EXIT_FAILURE);
	if (ft_strncmp("OLDPWD", str, 6) == 0)
		if (write(fd, path, ft_strlen(path)) == -1)
			return (EXIT_FAILURE);
	if (chdir(path) == -1)
		return (perror("cd"), EXIT_FAILURE);
	else
	{
		if (update_env(en, act_pwd) == 1)
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
}

int	ft_tilde(t_list **en, char *str, char act_pwd[1024])
{
	char	*dest;
	char	*home;

	home = ft_get_gvar_value("HOME", *en);
	if (!home)
		home = getenv("HOME");
	dest = ft_strjoin(home, str + 1, false, false);
	if (!dest)
		return (EXIT_FAILURE);
	if (chdir(dest) == -1)
		return (free(dest), perror("minishell: cd"), EXIT_FAILURE);
	else
	{
		free(dest);
		if (update_env(en, act_pwd) == 1)
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
}

int	ft_cd(char **args, t_list **en, int fd)
{
	char	act_pwd[1024];

	getcwd(act_pwd, 1024);
	if (!args[1])
		return (ft_go_to_path("HOME", en, act_pwd, fd));
	else if (args[1][0] == '-' && !args[1][1])
		return (ft_go_to_path("OLDPWD", en, act_pwd, fd));
	else if (args[1][0] == '~')
		return (ft_tilde(en, args[1], act_pwd));
	if (chdir(args[1]) == -1)
		return (perror("minishell: cd"), EXIT_FAILURE);
	else
	{
		if (update_env(en, act_pwd) == 1)
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
}
