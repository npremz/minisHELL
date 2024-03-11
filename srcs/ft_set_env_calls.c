/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_env_calls.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npremont <npremont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 22:10:33 by npremont          #+#    #+#             */
/*   Updated: 2024/03/11 17:53:05 by npremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_create_new_str(char **res, char *str, t_list *env_eff, t_list *en)
{
	int		i[3];

	i[0] = 0;
	i[1] = 0;
	while (str[i[0]])
	{
		if (str[i[0]] == '$')
		{
			if (env_eff->content)
			{
				if (ft_add_var_to_res(res, env_eff->content, en, i))
					return (EXIT_FAILURE);
				if (i[2] == 0)
					while (str[++(i[0])] && str[i[0]] != ' '
						&& str[i[0]] != '$')
						;
				env_eff = env_eff->next;
				continue ;
			}
			env_eff = env_eff->next;
		}
		(*res)[(i[1])++] = str[(i[0])++];
	}
	(*res)[i[1]] = '\0';
	return (EXIT_SUCCESS);
}

char	*ft_alloc_new_str(char *str, t_list *en, t_list *env_eff)
{
	int		len;
	int		i;
	char	*res;

	len = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '$')
		{
			if (env_eff->content)
				ft_add_var_len_to_res(&i, &len, env_eff->content, en);
			env_eff = env_eff->next;
		}
		++len;
	}
	return (res = malloc((len + 1) * sizeof(char)), res);
}

int	ft_handle_name(t_cmd *cmd, t_list *en)
{
	char	*res;
	int		i;

	i = 0;
	res = ft_alloc_new_str(cmd->name, en, cmd->env_eff_name);
	if (!res)
		return (EXIT_FAILURE);
	if (ft_create_new_str(&res, cmd->name, cmd->env_eff_name, en))
		return (EXIT_FAILURE);
	while (res[i])
	{
		if (res[i] == ' ')
			res[i] = '\0';
		++i;
	}
	free(cmd->name);
	cmd->name = res;
	return (EXIT_SUCCESS);
}

int	ft_handle_args(t_cmd *cmd, char ***cmd_tab, t_list *en, t_list *env_eff)
{
	char	**res_split;
	char	*res;
	char	*temp_str;

	(void)cmd;
	temp_str = ft_unsplit((*cmd_tab), " ");
	res = ft_alloc_new_str(temp_str, en, env_eff);
	if (!res)
		return (EXIT_FAILURE);
	if (ft_create_new_str(&res, temp_str, env_eff, en))
		return (EXIT_FAILURE);
	res_split = ft_split(res, ' ');
	if (!res_split)
		return (EXIT_FAILURE);
	free(res);
	ft_free_tab((*cmd_tab));
	(*cmd_tab) = res_split;
	return (EXIT_SUCCESS);
}

int	ft_set_env_calls(t_cmd *cmd, t_list *en, int debug)
{
	if (debug)
		ft_debug(cmd);
	if (cmd->env_eff_name && ft_handle_name(cmd, en))
		return (EXIT_FAILURE);
	ft_lstadd_back(&cmd->env_eff_name, cmd->env_eff_arg);
	if (cmd->arg && cmd->env_eff_name
		&& ft_handle_args(cmd, &cmd->arg, en, cmd->env_eff_name))
		return (EXIT_FAILURE);
	if (cmd->in && cmd->env_eff_in
		&& ft_handle_args(cmd, &cmd->in, en, cmd->env_eff_in))
		return (EXIT_FAILURE);
	if (cmd->out && cmd->env_eff_out
		&& ft_handle_args(cmd, &cmd->out, en, cmd->env_eff_out))
		return (EXIT_FAILURE);
	if (debug)
		ft_debug(cmd);
	return (EXIT_SUCCESS);
}
