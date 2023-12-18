/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_wildcard_cmd_list.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 17:59:54 by lethomas          #+#    #+#             */
/*   Updated: 2023/12/17 01:22:42 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing_exec.h"

static void	ft_update_wildcard_cmd(t_list *new_wildcard_cmd,
	t_list **wildcard_cmd, t_bool has_set_loc)
{
	t_list	*last_elem;

	if (new_wildcard_cmd != NULL)
	{
		last_elem = ft_lstlast(new_wildcard_cmd);
		new_wildcard_cmd->prev = (*wildcard_cmd)->prev;
		last_elem->next = (*wildcard_cmd)->next;
		if ((*wildcard_cmd)->prev != NULL)
			(*wildcard_cmd)->prev->next = new_wildcard_cmd;
		if ((*wildcard_cmd)->next != NULL)
			(*wildcard_cmd)->next->prev = last_elem;
	}
	if (new_wildcard_cmd == NULL && has_set_loc == true)
	{
		if ((*wildcard_cmd)->prev != NULL)
			(*wildcard_cmd)->prev->next = (*wildcard_cmd)->next;
		if ((*wildcard_cmd)->next != NULL)
			(*wildcard_cmd)->next->prev = (*wildcard_cmd)->prev;
	}
}

static t_list	*ft_set_elem_prev_next(t_list *new_wildcard_cmd,
	t_list **wildcard_cmd, t_bool has_set_loc, t_list **elem_prev)
{
	t_list *elem_next;
	t_list	*last_elem;

	if (new_wildcard_cmd != NULL)
	{
		last_elem = ft_lstlast(new_wildcard_cmd);
		*elem_prev = last_elem;
		elem_next = last_elem->next;
	}
	else if (new_wildcard_cmd == NULL && has_set_loc == true)
	{
		*elem_prev = (*wildcard_cmd)->prev;
		elem_next = (*wildcard_cmd)->next;
	}
	else
	{
		*elem_prev = *wildcard_cmd;
		elem_next = (*wildcard_cmd)->next;
	}
	return (elem_next);
}

static t_bool	ft_shift_wildcard_cmd(t_list *new_wildcard_cmd,
	t_list **wildcard_cmd, t_bool has_set_loc)
{
	t_list *elem_prev;
	t_list *elem_next;

	elem_next = ft_set_elem_prev_next(new_wildcard_cmd, wildcard_cmd,
		has_set_loc, &elem_prev);
	if (has_set_loc == true)
	{
		ft_free_cmd((*wildcard_cmd)->content);
		free(*wildcard_cmd);
	}
	if (elem_next == NULL)
	{
		*wildcard_cmd = elem_prev;
		if (elem_prev != NULL)
			while ((*wildcard_cmd)->prev != NULL)
				*wildcard_cmd = (*wildcard_cmd)->prev;
		return (true);
	}
	*wildcard_cmd = elem_next;
	return (false);
}

static int	ft_wildcard_cmd_list_loop(t_list **wildcard_cmd,
	t_bool *has_set)
{
	t_bool	has_set_loc;
	t_list	*new_wildcard_cmd;

	if (ft_set_wildcard_cmd_list((t_cmd *)(*wildcard_cmd)->content,
			&new_wildcard_cmd, &has_set_loc))
		return (EXIT_FAILURE);
	if (*has_set == false)
		*has_set = has_set_loc;
	ft_update_wildcard_cmd(new_wildcard_cmd, wildcard_cmd,
		has_set_loc);
	if (ft_shift_wildcard_cmd(new_wildcard_cmd, wildcard_cmd,
			has_set_loc))
		return (2);
	return (EXIT_SUCCESS);
}

int	ft_get_wildcard_cmd_list(t_cmd *cmd, t_list **wildcard_cmd)
{
	t_cmd	*cmd_cpy;
	t_bool	has_set;
	int		return_value;

	has_set = true;
	if (ft_copy_cmd(cmd, &cmd_cpy))
		return (EXIT_FAILURE);
	*wildcard_cmd = ft_lstnew(cmd_cpy);
	if (*wildcard_cmd == NULL)
		return (EXIT_FAILURE);
	while (has_set == true)
	{
		has_set = false;
		while (*wildcard_cmd != NULL)
		{
			return_value = ft_wildcard_cmd_list_loop(wildcard_cmd,
				&has_set);
			if (return_value == EXIT_FAILURE)
				return (EXIT_FAILURE);
			if (return_value == 2)
				break ;
		}
	}
	return (EXIT_SUCCESS);
}
