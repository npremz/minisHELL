/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npremont <npremont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 13:28:29 by npremont          #+#    #+#             */
/*   Updated: 2023/12/13 18:55:10 by npremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getvarvalue(char *line)
{
	size_t	i;
	size_t	j;
	char	*value;

	i = 0;
	j = 0;
	while (line[i] != '=' && line[i])
		++i;
	if (line[i])
		++i;
	j = i;
	while (line[i])
		++i;
	value = malloc((i - j + 1) * sizeof(char));
	if (!value)
		return (NULL);
	i = 0;
	while (line[j])
	{
		value[i] = line[j];
		++i;
		++j;
	}
	value[i] = '\0';
	return (value);
}

char	*ft_getvarname(char *line)
{
	size_t	i;
	char	*name;

	i = 0;
	while (line[i] != '=' && line[i])
		++i;
	name = malloc((i + 1) * sizeof(char));
	if (!name)
		return (NULL);
	if (!line[i])
	{
		name[0] = '\0';
		return (name);
	}
	i = 0;
	if (line[i] == '=')
		return (write(2, "export: not a valid identifier\n", 32), name);
	while (line[i] != '=' && line[i])
	{
		name[i] = line[i];
		++i;
	}
	name[i] = '\0';
	return (name);
}

t_globvar	*ft_newvar(char *line)
{
	t_globvar	*var;

	var = malloc(sizeof(t_globvar));
	if (!var)
		return (NULL);
	var->name = ft_getvarname(line);
	if (!var->name)
		return (NULL);
	var->value = ft_getvarvalue(line);
	if (!var->value)
		return (NULL);
	return (var);
}

int	ft_envinit(char **envp)
{
	size_t		i;
	t_list		*node;
	t_globvar	*var;

	i = 0;
	while (envp[i])
	{
		var = NULL;
		var = ft_newvar(envp[i]);
		if (!var)
			return (ft_lstclear(&env_list, free), -1);
		node = ft_lstnew(var);
		if (!node)
			return (ft_lstclear(&env_list, free), -1);
		ft_lstadd_back(&env_list, node);
		++i;
	}
	return (0);
}
