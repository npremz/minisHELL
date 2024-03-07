/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcard_cmp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 23:58:01 by lethomas          #+#    #+#             */
/*   Updated: 2024/03/07 14:13:17 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_bool	ft_cmp_operation(char *with_wildcard, char **without_wildcard,
	int begin, int end)
{
	char	*without_wildcard_temp;
	t_bool	is_end_reach;

	is_end_reach = (with_wildcard[end] == '\0');
	with_wildcard[end] = '\0';
	without_wildcard_temp = ft_strnstr(*without_wildcard,
			with_wildcard + begin, ft_strlen(*without_wildcard) + 1);
	if (is_end_reach == false)
		with_wildcard[end] = '*';
	if (without_wildcard_temp == NULL)
		return (false);
	if (begin == 0 && *without_wildcard != without_wildcard_temp)
		return (false);
	*without_wildcard = without_wildcard_temp + end - begin;
	return (true);
}

static t_bool	ft_set_begin_end(char *with_wildcard,
	t_list **wildcard_list, int *begin, int *end)
{
	while (with_wildcard[*begin] == '*'
		&& *((t_bool *)(*wildcard_list)->content) == true)
	{
		*wildcard_list = (*wildcard_list)->next;
		(*begin)++;
	}
	if (with_wildcard[*begin] == '\0')
		return (true);
	*end = *begin;
	while (with_wildcard[*end] != '\0'
		&& (with_wildcard[*end] != '*'
			|| *((t_bool *)(*wildcard_list)->content) == false))
	{
		if (with_wildcard[*end] == '*')
			*wildcard_list = (*wildcard_list)->next;
		(*end)++;
	}
	return (false);
}

t_bool	ft_wildcard_cmp_recursive(char *with_wildcard, char *without_wildcard,
	t_list *wildcard_list, int begin)
{
	int		end;
	t_bool	is_end_reach;

	is_end_reach = false;
	if (ft_set_begin_end(with_wildcard, &wildcard_list, &begin, &end) == true)
		return (true);
	is_end_reach = (with_wildcard[end] == '\0');
	while (ft_cmp_operation(with_wildcard, &without_wildcard, begin, end)
		== true)
	{
		if (is_end_reach == true)
		{
			if (*without_wildcard == '\0')
				return (true);
		}
		else
			if (ft_wildcard_cmp_recursive(with_wildcard, without_wildcard,
					wildcard_list, end) == true)
				return (true);
	}
	return (false);
}

t_bool	ft_wildcard_cmp(char *with_wildcard, char *without_wildcard,
	t_list *wildcard_list)
{
	return (ft_wildcard_cmp_recursive(with_wildcard, without_wildcard,
			wildcard_list, 0));
}
