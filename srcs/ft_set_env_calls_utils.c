/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_env_calls_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npremont <npremont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:33:01 by npremont          #+#    #+#             */
/*   Updated: 2024/03/14 18:48:44 by npremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_unsplit(char **tab, char *c)
{
	int		i;
	char	*res;

	i = 0;
	res = ft_calloc(1, 1);
	if (!res)
		return (NULL);
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
	char	*tmp;

	var_value = ft_get_gvar_value(var_name + 1, en);
	if (var_value)
		*len += ft_strlen(var_value) + 1;
	else if (*(var_name + 1) == '?')
	{
		tmp = ft_itoa(g_sig.exit_status);
		*len += ft_strlen(tmp);
		free(tmp);
	}
	else if (*(var_name + 1) == '_')
		*len += ft_strlen("/usr/bin/env");
	else
		++(*len);
	if (var_value || *(var_name + 1) == '?' || *(var_name + 1) == '_')
		*i += ft_strlen(var_name) - 1;
	else
		++(*i);
}

int	ft_add_var_to_res(char **res, char *var, t_list *en, int i[3])
{
	char	*var_value;
	char	*status_str;

	(*res)[i[1]] = '\0';
	status_str = ft_itoa(g_sig.exit_status);
	var_value = ft_get_gvar_value(var + 1, en);
	if (var_value)
		ft_strlcat((*res), var_value, i[3]);
	else if (*(var + 1) == '?')
		ft_strlcat((*res), status_str, i[3]);
	else if (*(var + 1) == '_')
		ft_strlcat((*res), "/usr/bin/env", i[3]);
	if (ft_strncmp("$", var, 2) == 0)
		ft_strlcat((*res), "$", i[3] + 1);
	if (var_value || *(var + 1) == '?' || *(var + 1) == '_'
		|| ft_strncmp("$", var, 2) == 0)
	{
		i[0] += ft_strlen(var);
		i[1] = ft_strlen(*(res));
		i[2] = 1;
	}
	else
		i[2] = 0;
	return (free(status_str), EXIT_SUCCESS);
}
