/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npremont <npremont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 15:03:52 by npremont          #+#    #+#             */
/*   Updated: 2024/03/07 10:57:26 by npremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_input_type(char *arg)
{
	size_t	i;

	i = 0;
	if (ft_isalpha(arg[i]) == 0 && arg[i] != '_')
		return (write(2, "minishell: export: ", 9), write(2, "`", 1),
			write(2, arg, ft_strlen(arg)), write(2, "'", 1), 
			write(2, ": not a valid identifier\n", 26));
	++i;
	while (arg[i] != '=' && arg[i] != '\0')
	{
		if (arg[i] == '+' && arg[i + 1] == '=')
			return (1);
		if (ft_isalnum(arg[i]) == 0 && arg[i] != '_')
			return (write(2, "minishell: export: ", 9), write(2, "`", 1),
				write(2, arg, ft_strlen(arg)), write(2, "'", 1), 
				write(2, ": not a valid identifier\n", 26));
		++i;
	}
	if (arg[i] == '=')
		return (2);
	else
		return (3);
}

int	add_content_to_var(t_list **en, t_globvar *tmp, t_globvar *var)
{
	char	*tmp_str;
	t_list	*new;

	if (tmp)
	{
		tmp_str = tmp->value;
		tmp->value = ft_strjoin(tmp->value, var->value, false, false);
		free(tmp_str);
		free_globvar(var);
		if (!tmp->value)
			return (EXIT_FAILURE);
	}
	else
	{
		var->is_secret = 0;
		new = ft_lstnew(var);
		if (!new)
			return (EXIT_FAILURE);
		ft_lstadd_back(en, new);
	}
	return (EXIT_SUCCESS);
}

int	update_var(t_list **en, t_globvar *tmp, t_globvar *var, int type)
{
	t_list	*new;

	if (tmp)
	{
		if (type == 2)
		{
			free(tmp->value);
			tmp->value = var->value;
			free(var->name);
		}
	}
	else
	{
		if (type == 3)
			var->is_secret = 1;
		else
			var->is_secret = 0;
		new = ft_lstnew(var);
		if (!new)
			return (EXIT_FAILURE);
		ft_lstadd_back(en, new);
	}
	return (EXIT_SUCCESS);
}

int	ft_export_var(int type, t_list *en, t_globvar *var)
{
	t_globvar	*tmp;
	t_list		*en_start;

	tmp = NULL;
	en_start = en;
	while (en)
	{
		tmp = en->content;
		if (ft_strncmp(var->name, tmp->name, ft_strlen(var->name)) == 0)
			break ;
		else
			tmp = NULL;
		en = en->next;
	}
	if (type == 1)
		return (add_content_to_var(&en_start, tmp, var));
	if (type == 2 || type == 3)
		return (update_var(&en_start, tmp, var, type));
	return (EXIT_FAILURE);
}

int	ft_export(char **args, t_list **en, int fd)
{
	size_t		i;
	int			type;
	t_globvar	*var;
	char		*plus_char;

	if (!args[1])
		return (ft_print_secret(*en, fd));
	i = 1;
	while (args[i])
	{
		type = get_input_type(args[1]);
		var = malloc(sizeof(t_globvar));
		if (!var)
			return (EXIT_FAILURE);
		if (ft_get_globvar(args[i], &var) == 0)
			return (free(var), EXIT_FAILURE);
		plus_char = ft_strchr(var->name, '+');
		if (plus_char)
			*plus_char = '\0';
		if (ft_export_var(type, *en, var) == 1)
			return (free_globvar(var), EXIT_FAILURE);
		++i;
	}
	return (EXIT_SUCCESS);
}
