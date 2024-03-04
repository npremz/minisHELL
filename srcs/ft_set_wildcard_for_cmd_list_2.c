/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_wildcard_for_cmd_list_2.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 20:38:04 by lethomas          #+#    #+#             */
/*   Updated: 2023/12/19 21:52:41 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing_exec.h"

static void	ft_set_front_first_elem_alpha_order(t_list *list)
{
	void	*content_temp;

	while (list->next != NULL)
		list = list->next;
	while (list->prev != NULL)
	{
		if (ft_strncmp((char *)list->content, (char *)list->prev->content,
				ft_strlen((char *)list->content) + 1) < 0)
		{
			content_temp = list->content;
			list->content = list->prev->content;
			list->prev->content = content_temp;
		}
		list = list->prev;
	}
}

static int	ft_set_new_name(t_cmd *cmd, t_list *new_name)
{
	ft_set_front_first_elem_alpha_order(new_name);
	free(cmd->name);
	cmd->name = (char *)new_name->content;
	free(cmd->arg[0]);
	cmd->arg[0] = ft_strdup((char *)new_name->content);
	if (cmd->arg[0] == NULL)
		return (EXIT_FAILURE);
	ft_lstclear(&new_name->next, &free);
	free(new_name);
	return (EXIT_SUCCESS);
}

int	ft_set_wildcard_for_cmd_name(t_cmd *cmd)
{
	t_list	*new_name;
	t_list	*wildcard_bool_list_temp;

	wildcard_bool_list_temp = cmd->wildcard_name->prev;
	if (ft_get_wildcard_value(cmd->name, &cmd->wildcard_name, &new_name))
		return (EXIT_FAILURE);
	if (new_name != NULL)
		if (ft_set_new_name(cmd, new_name))
			return (EXIT_FAILURE);
	if (ft_update_wildcard_bool_list_new_entry(cmd->wildcard_name,
			cmd->name, &wildcard_bool_list_temp))
		return (EXIT_FAILURE);
	if (cmd->wildcard_name == NULL)
		cmd->wildcard_name = wildcard_bool_list_temp;
	if (cmd->wildcard_name != NULL)
		while (cmd->wildcard_name->prev != NULL)
			cmd->wildcard_name = cmd->wildcard_name->prev;
	return (EXIT_SUCCESS);
}
