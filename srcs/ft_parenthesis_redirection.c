/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parenthesis_redirection.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 20:45:03 by lethomas          #+#    #+#             */
/*   Updated: 2023/12/12 01:08:16 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

static void	ft_lstinsert_back_redirection(t_list *elem,
	t_list *elem_to_insert_prev)
{
	t_list *elem_to_insert;

	elem_to_insert = elem_to_insert_prev->next;
	elem_to_insert_prev->next = elem_to_insert->next;
	elem_to_insert->next = elem->next;
	elem->next = elem_to_insert;
}

static int	ft_set_cmd_in(t_list *token_list_prev, t_list *token_list,
	t_list **elem_receiver_in)
{
	if (token_list_prev != NULL
		&& ((t_token *)token_list_prev->content)->type != pipe_operator
		&& ((t_token *)token_list_prev->content)->type != and_operator
		&& ((t_token *)token_list_prev->content)->type != or_operator)
		return (EXIT_FAILURE);
	(*elem_receiver_in) = token_list;
	while (((t_token *)(*elem_receiver_in)->content)->type == left_parenthesis
		&& ((t_token *)(*elem_receiver_in)->next->content)->type
		== left_parenthesis)
		(*elem_receiver_in) = (*elem_receiver_in)->next;
	return (EXIT_SUCCESS);
}

static int	ft_set_cmd_out(t_list **elem_to_insert_prev,
	t_list **elem_receiver_out)
{
	int		counter_parenthesis;
	t_token	*token_to_insert_prev;

	counter_parenthesis = 1;
	while (counter_parenthesis != 0)
	{
		token_to_insert_prev = (t_token *)(*elem_to_insert_prev)->content;
		if (token_to_insert_prev->type == left_parenthesis)
			counter_parenthesis++;
		if (token_to_insert_prev->type == right_parenthesis)
			counter_parenthesis--;
		if (token_to_insert_prev->type == pipe_operator
			|| token_to_insert_prev->type == and_operator
			|| token_to_insert_prev->type == or_operator)
		{
				*elem_receiver_out = *elem_to_insert_prev;
				while (((t_token *)(*elem_receiver_out)->next->content)->type
					== left_parenthesis)
					*elem_receiver_out = (*elem_receiver_out)->next;
		}
		if (counter_parenthesis != 0)
			*elem_to_insert_prev = (*elem_to_insert_prev)->next;
		if (*elem_to_insert_prev == NULL)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	ft_move_redirection(t_list *elem_to_insert_prev,
	t_list	*elem_receiver_in, t_list *elem_receiver_out)
{
	while (elem_to_insert_prev->next != NULL
		&& ((t_token *)elem_to_insert_prev->next->content)->type != pipe_operator
		&& ((t_token *)elem_to_insert_prev->next->content)->type != and_operator
		&& ((t_token *)elem_to_insert_prev->next->content)->type != or_operator)
	{
		if (elem_to_insert_prev->next->next == NULL
			|| ((t_token *)elem_to_insert_prev->next->next->content)->type != word)
			return (EXIT_FAILURE);
		if (((t_token *)elem_to_insert_prev->next->content)->type == redirection_in
			|| ((t_token *)elem_to_insert_prev->next->content)->type == redirection_here_doc)
		{
			ft_lstinsert_back_redirection(elem_receiver_in, elem_to_insert_prev);
			elem_receiver_in = elem_receiver_in->next;
			ft_lstinsert_back_redirection(elem_receiver_in, elem_to_insert_prev);
			elem_receiver_in = elem_receiver_in->next;
		}
		else if (((t_token *)elem_to_insert_prev->next->content)->type == redirection_out
			|| ((t_token *)elem_to_insert_prev->next->content)->type == redirection_append)
		{
			ft_lstinsert_back_redirection(elem_receiver_out, elem_to_insert_prev);
			elem_receiver_out = elem_receiver_out->next;
			ft_lstinsert_back_redirection(elem_receiver_out, elem_to_insert_prev);
			elem_receiver_out = elem_receiver_out->next;
		}
		else
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	ft_parenthesis_redirection(t_list *token_list)
{
	t_list	*elem_receiver_in;
	t_list	*elem_receiver_out;
	t_list *token_list_prev;
	t_list *elem_to_insert_prev;

	token_list_prev = NULL;
	while (token_list != NULL)
	{
		if (((t_token *)token_list->content)->type == left_parenthesis)
		{
			if (ft_set_cmd_in(token_list_prev, token_list, &elem_receiver_in))
				return (EXIT_FAILURE);
			elem_to_insert_prev = token_list->next;
			elem_receiver_out = elem_receiver_in;
			if (ft_set_cmd_out(&elem_to_insert_prev, &elem_receiver_out))
				return (EXIT_FAILURE);
			if (ft_move_redirection(elem_to_insert_prev, elem_receiver_in,
				elem_receiver_out))
				return (EXIT_FAILURE);
		}
		token_list_prev = token_list;
		token_list = token_list->next;
	}
	return (EXIT_SUCCESS);
}
