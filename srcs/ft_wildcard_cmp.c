/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcard_cmp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 23:58:01 by lethomas          #+#    #+#             */
/*   Updated: 2023/12/19 00:09:44 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing_exec.h"

void	ft_set_end(char *with_wildcard,
	t_list **wildcard_list, int *end)
{
	while (with_wildcard[*end] != '\0'
		&& (with_wildcard[*end] != '*'
			|| *((t_bool *)(*wildcard_list)->content) == false))
	{
		if (with_wildcard[*end] == '*')
			*wildcard_list = (*wildcard_list)->next;
		(*end)++;
	}
}

static t_bool	ft_cmp_operation(char *with_wildcard, char **without_wildcard,
	int begin, int end)
{
	char	*without_wildcard_temp;
	t_bool	is_end_reach;

	is_end_reach = false;
	if (with_wildcard[end] == '\0')
		is_end_reach = true;
	with_wildcard[end] = '\0';
	without_wildcard_temp = ft_strnstr(*without_wildcard,
			with_wildcard + begin, ft_strlen(*without_wildcard) + 1);
	if (is_end_reach == false)
		with_wildcard[end] = '*';
	if (begin == 0 && *without_wildcard != without_wildcard_temp)
		return (false);
	if (without_wildcard_temp == NULL)
		return (false);
	*without_wildcard = without_wildcard_temp + end - begin;
	return (true);
}

static t_bool	ft_set_begin(char *with_wildcard,
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
	return (false);
}

t_bool	ft_wildcard_cmp(char *with_wildcard, char *without_wildcard,
	t_list *wildcard_list)
{
	int		begin;
	int		end;
	t_bool	is_end_reach;

	begin = 0;
	is_end_reach = false;
	while (is_end_reach == false)
	{
		if (ft_set_begin(with_wildcard, &wildcard_list, &begin, &end) == true)
			return (true);
		ft_set_end(with_wildcard, &wildcard_list, &end);
		is_end_reach = (with_wildcard[end] == '\0');
		if (ft_cmp_operation(with_wildcard, &without_wildcard,
				begin, end) == false)
			return (false);
		if (is_end_reach == true)
			return (*without_wildcard == '\0');
		begin = end;
	}
	return (true);
}
