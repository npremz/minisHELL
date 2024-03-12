/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_env_calls_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npremont <npremont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:33:01 by npremont          #+#    #+#             */
/*   Updated: 2024/03/12 11:54:16 by npremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_unsplit(char **tab, char *c)
{
	int		i;
	char	*res;

	i = 0;
	res = ft_calloc(1, 1);
	while (tab[i])
	{
		res = ft_strjoin(res, tab[i], true, false);
		if (!res)
			return (NULL);
		if (tab[i + 1])
		{
			res = ft_strjoin(res, c, true, false);
			if (!res)
				return (NULL);
		}
		++i;
	}
	return (res);
}

void	ft_debug(t_cmd *cmd)
{
	int	i;

	i = -1;
	printf("\n");
	printf("== == == DEBUG == == ==\n\n");
	printf("\tname: %s\n", cmd->name);
	printf("\targs:\n");
	while ((cmd->arg)[++i])
		printf("\t\t%s\n", (cmd->arg)[i]);
	i = -1;
	printf("\tins:\n");
	while ((cmd->in)[++i])
		printf("\t\t%s\n", (cmd->arg)[i]);
	i = -1;
	printf("\touts:\n");
	while ((cmd->in)[++i])
		printf("\t\t%s\n", (cmd->arg)[i]);
	printf("\n\n\n");
}

void	ft_add_var_len_to_res(int *i, int *len, char *var_name, t_list *en)
{
	char	*var_value;

	++(*i);
	var_value = ft_get_gvar_value(var_name, en);
	if (var_value)
	{
		*i += ft_strlen(var_name);
		*len += ft_strlen(var_value);
	}
	else
		++(*len);
}

int	ft_add_var_to_res(char **res, char *var, t_list *en, int i[3])
{
	char	*var_value;

	var_value = ft_get_gvar_value(var + 1, en);
	if (var_value)
	{
		(*res)[i[1]] = '\0';
		(*res) = ft_strjoin((*res), var_value, true, false);
		if (!(*res))
			return (EXIT_FAILURE);
		i[0] += ft_strlen(var);
		i[1] = ft_strlen(*(res));
		i[2] = 1;
	}
	else
		i[2] = 0;
	return (EXIT_SUCCESS);
}
