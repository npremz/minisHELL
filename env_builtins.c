/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npremont <npremont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 15:19:27 by npremont          #+#    #+#             */
/*   Updated: 2023/12/13 19:00:16 by npremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(void)
{
	if (!env_list)
		return ;
	while (env_list)
	{
		ft_printf("%s=%s\n", ((t_globvar *)env_list->content)->name,
			((t_globvar *)env_list->content)->value);
		env_list = env_list->next;
	}
}

void	ft_handlevar(char *name, char *value)
{
	t_globvar	*var;
	t_list		*node;

	if (!name[0])
		return ;
	var = NULL;
	var = malloc(sizeof(t_globvar));
	var->name = name;
	var->value = value;
	node = ft_lstnew(var);
	if (!node)
		return ;
	ft_lstadd_back(&env_list, node);
}

void	ft_export(char *arg)
{
	char		**args;
	char		*name;
	char		*value;
	size_t		i;

	args = ft_split(arg, ' ');
	if (!args)
	{
		write(2, "memory problem\n", 16);
		return ;
	}
	i = 1;
	while (args[i])
	{
		name = ft_getvarname(args[i]);
		if (!name)
			return ;
		value = ft_getvarvalue(args[i]);
		if (!value)
			return ;
		ft_handlevar(name, value);
		++i;
	}
	ft_free_split(args);
}
