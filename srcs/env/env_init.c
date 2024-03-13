/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npremont <npremont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 10:58:51 by npremont          #+#    #+#             */
/*   Updated: 2024/03/13 11:13:53 by npremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_initshlvl(t_list **en)
{
	t_globvar	*var;
	char		*shlvl;
	int			lvl;

	var = malloc(sizeof(t_globvar));
	if (!var)
		return (EXIT_FAILURE);
	var->name = ft_strdup("SHLVL");
	if (!var->name)
		return (free(var), EXIT_FAILURE);
	shlvl = ft_get_gvar_value("SHLVL", *en);
	if (!shlvl)
		lvl = 1;
	else
	{
		lvl = ft_atoi(shlvl, 0) + 1;
		if (lvl < 0)
			lvl = 0;
	}
	var->value = ft_itoa(lvl);
	if (!var->value)
		return (free(var->name), free(var), EXIT_FAILURE);
	if (ft_export_var(2, en, var))
		return (EXIT_FAILURE);
	return (free(var), EXIT_SUCCESS);
}

int	ft_initpwd(t_list **en)
{
	t_globvar	*var;
	char		pwd[1024];

	if (!getcwd(pwd, sizeof(pwd)))
		return (EXIT_FAILURE);
	var = malloc(sizeof(t_globvar));
	if (!var)
		return (EXIT_FAILURE); 
	var->name = ft_strdup("PWD");
	if (!var->name)
		return (free(var), EXIT_FAILURE);
	var->value = ft_strdup(pwd);
	if (!var->value)
		return (free(var->name), free(var), EXIT_FAILURE);
	if (ft_export_var(2, en, var))
		return (EXIT_FAILURE);
	return (free(var), EXIT_SUCCESS);
}

int	ft_print_secret(t_list *en, int fd)
{
	char	**en_tab;
	char	*tmp;
	size_t	i;

	if (!en)
		return (EXIT_SUCCESS);
	en_tab = ft_en_to_tab(en);
	if (!en_tab)
		return (EXIT_FAILURE);
	i = 0;
	while (en_tab[++i])
	{
		if (ft_strncmp(en_tab[i], en_tab[i - 1], ft_strlen(en_tab[i - 1])) < 0)
		{
			tmp = en_tab[i];
			en_tab[i] = en_tab[i - 1];
			en_tab[i - 1] = tmp;
			i = 0;
		}
	}
	if (ft_print_export(en_tab, fd))
		return (EXIT_FAILURE);
	ft_free_tab(en_tab);
	return (EXIT_SUCCESS);
}

int	ft_get_globvar(char *varline, t_globvar **var)
{
	(*var)->name = ft_get_varname(varline);
	if (!(*var)->name)
		return (0);
	(*var)->value = ft_get_varvalue(varline);
	if (!(*var)->name)
		return (free((*var)->name), 0);
	return (1);
}

void	ft_envinit(t_list **en, char **envp)
{
	size_t		i;
	t_list		*new_node;
	t_globvar	*var;

	i = -1;
	var = NULL;
	new_node = NULL;
	while (envp && envp[++i] && envp[i + 1]) //
	{
		var = malloc(sizeof(t_globvar));
		if (!var)
			exit_error("Error: Init failed.\n", en, var, EXIT_FAILURE);
		if (ft_get_globvar(envp[i], &var) == 0)
			exit_error("Error: Init failed.\n", en, var, EXIT_FAILURE);
		new_node = ft_lstnew(var);
		var->is_secret = 0;
		if (!new_node)
			exit_error("Error: Init failed.\n", en, var, EXIT_FAILURE);
		ft_lstadd_back(en, new_node);
	}
	if (ft_initshlvl(en))
		exit_error("Error: Init failed.\n", en, NULL, EXIT_FAILURE);
	if (ft_initpwd(en))
		exit_error("Error: Init failed.\n", en, NULL, EXIT_FAILURE);
}
