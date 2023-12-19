/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update_wildcard_bool_list.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 21:24:45 by lethomas          #+#    #+#             */
/*   Updated: 2023/12/18 21:38:44 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing_exec.h"

static void	ft_add_wildcard_bool_list(t_list **wildcard_bool_list,
	t_list *new_elem, t_bool *switch_case)
{
	if (*wildcard_bool_list == NULL)
	{
		*wildcard_bool_list = new_elem;
		*switch_case = true;
	}
	else if ((*wildcard_bool_list)->prev != NULL || *switch_case == true)
	{
		new_elem->prev = *wildcard_bool_list;
		new_elem->next = (*wildcard_bool_list)->next;
		if ((*wildcard_bool_list)->next != NULL)
			(*wildcard_bool_list)->next->prev = new_elem;
		(*wildcard_bool_list)->next = new_elem;
		*wildcard_bool_list = new_elem;
	}
	else
	{
		new_elem->next = *wildcard_bool_list;
		(*wildcard_bool_list)->prev = new_elem;
		*wildcard_bool_list = new_elem;
		*switch_case = true;
	}
}

int	ft_update_wildcard_bool_list_new_entry(t_list **wildcard_bool_list,
	char *name, t_bool switch_case)
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
				new_elem, &switch_case);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

static void	ft_delete_wildcard_list(char *wildcard_name,
	t_list **wildcard_list)
{
	int		i;
	t_list	*elem_list;
	t_list	*new_begin;

	i = 0;
	new_begin = (*wildcard_list)->prev;
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
	if (new_begin != NULL)
		*wildcard_list = new_begin;
}

static void	ft_replace_effective_wildcard(char *wildcard_name,
	t_list *wildcard_list)
{
	int		i;

	i = 0;
	while (wildcard_name[i] != '\0')
	{
		if (wildcard_name[i] == '*')
		{
			if (*((t_bool *)wildcard_list->content) == true)
				*((t_bool *)wildcard_list->content) = false;
			wildcard_list = wildcard_list->next;
		}
		i++;
	}
}

void	ft_update_wildcard_bool_list_old_entry(t_list *wildcard_value_list,
	char *wildcard_name, t_list **wildcard_list)
{
	if (wildcard_value_list != NULL)
		ft_delete_wildcard_list(wildcard_name, wildcard_list);
	else
		ft_replace_effective_wildcard(wildcard_name, *wildcard_list);
}
