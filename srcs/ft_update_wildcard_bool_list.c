/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update_wildcard_bool_list.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 21:24:45 by lethomas          #+#    #+#             */
/*   Updated: 2024/03/07 14:13:17 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_add_wildcard_bool_list(t_list *wildcard_bool_list,
	t_list *new_elem, t_list **elem_prev)
{
	if (wildcard_bool_list == NULL && *elem_prev == NULL)
	{
		*elem_prev = new_elem;
	}
	else if (wildcard_bool_list != NULL)
	{
		new_elem->prev = wildcard_bool_list->prev;
		new_elem->next = wildcard_bool_list;
		if (wildcard_bool_list->prev != NULL)
			wildcard_bool_list->prev->next = new_elem;
		wildcard_bool_list->prev = new_elem;
	}
	else if (wildcard_bool_list == NULL)
	{
		new_elem->prev = *elem_prev;
		(*elem_prev)->next = new_elem;
		*elem_prev = new_elem;
	}
}

int	ft_update_wildcard_bool_list_new_entry(t_list *wildcard_bool_list,
	char *name, t_list **elem_prev)
{
	int		i;
	t_bool	*new_content;
	t_list	*new_elem;

	i = 0;
	while (name[i] != '\0')
	{
		if (name[i] == '*')
		{
			new_content = (t_bool *)malloc(sizeof(t_bool));
			if (new_content == NULL)
				return (EXIT_FAILURE);
			*new_content = false;
			new_elem = ft_lstnew(new_content);
			if (new_elem == NULL)
				return (EXIT_FAILURE);
			ft_add_wildcard_bool_list(wildcard_bool_list,
				new_elem, elem_prev);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

void	ft_update_wildcard_bool_list_old_entry(char *wildcard_name,
	t_list **wildcard_list)
{
	int		i;
	t_list	*elem_list;

	i = 0;
	while (wildcard_name[i] != '\0')
	{
		if (wildcard_name[i] == '*')
		{
			elem_list = (*wildcard_list)->next;
			if ((*wildcard_list)->prev != NULL)
				(*wildcard_list)->prev->next = (*wildcard_list)->next;
			if ((*wildcard_list)->next != NULL)
				(*wildcard_list)->next->prev = (*wildcard_list)->prev;
			free((*wildcard_list)->content);
			free(*wildcard_list);
			*wildcard_list = elem_list;
		}
		i++;
	}
}
