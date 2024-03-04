/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update_path_before.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 19:20:57 by lethomas          #+#    #+#             */
/*   Updated: 2023/12/19 21:50:25 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing_exec.h"

static void	ft_update_path_before_null_case(t_list **path_before)
{
	t_list	*temp_elem;

	temp_elem = (*path_before)->next;
	if ((*path_before)->prev != NULL)
		(*path_before)->prev->next = (*path_before)->next;
	if ((*path_before)->next != NULL)
		(*path_before)->next->prev = (*path_before)->prev;
	free((*path_before)->content);
	free(*path_before);
	*path_before = temp_elem;
}

static int	ft_update_path_before_non_null_case(t_list **path_before,
	t_list *wildcard_value_list)
{
	t_list	*temp_elem;

	temp_elem = wildcard_value_list;
	while (wildcard_value_list != NULL)
	{
		wildcard_value_list->content
			= ft_strjoin((char *)(*path_before)->content,
				(char *)wildcard_value_list->content, false, true);
		if (wildcard_value_list == NULL)
			return (EXIT_FAILURE);
		wildcard_value_list = wildcard_value_list->next;
	}
	wildcard_value_list = temp_elem;
	wildcard_value_list->prev = (*path_before)->prev;
	temp_elem = ft_lstlast(wildcard_value_list);
	temp_elem->next = (*path_before)->next;
	if ((*path_before)->prev != NULL)
		(*path_before)->prev->next = wildcard_value_list;
	if ((*path_before)->next != NULL)
		(*path_before)->next->prev = temp_elem;
	free((*path_before)->content);
	free(*path_before);
	*path_before = temp_elem->next;
	return (EXIT_SUCCESS);
}

int	ft_update_path_before(t_list **path_before,
	t_list *wildcard_value_list)
{
	if (wildcard_value_list != NULL)
	{
		if (ft_update_path_before_non_null_case(path_before,
				wildcard_value_list))
			return (EXIT_FAILURE);
	}
	else
		ft_update_path_before_null_case(path_before);
	return (EXIT_SUCCESS);
}
