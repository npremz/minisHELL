/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_wildcard_name_path.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 18:52:44 by lethomas          #+#    #+#             */
/*   Updated: 2024/03/07 14:13:17 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_set_begin_wildcard_name(char **path_after, int *begin, int *end,
	t_list **wildcard_bool_list)
{
	*begin = 0;
	*end = 0;
	while ((*path_after)[*begin] != '\0'
		&& ((*path_after)[*begin] != '*'
			|| *((t_bool *)(*wildcard_bool_list)->content) == false))
	{
		if ((*path_after)[*begin] == '*')
			*wildcard_bool_list = (*wildcard_bool_list)->next;
		(*begin)++;
	}
	if ((*path_after)[*begin] == '\0')
		return ;
	while (*begin != 0 && (*path_after)[*begin] != '/')
	{
		(*begin)--;
		if ((*path_after)[*begin] == '*')
			*wildcard_bool_list = (*wildcard_bool_list)->prev;
	}
	*begin += ((*path_after)[*begin] == '/');
}

static int	ft_add_to_path_before(t_list *path_before, char *path_before_str)
{
	while (path_before != NULL)
	{
		path_before->content = ft_strjoin((char *)path_before->content,
				path_before_str, true, false);
		if (path_before->content == NULL)
			return (EXIT_FAILURE);
		path_before = path_before->next;
	}
	free(path_before_str);
	return (EXIT_SUCCESS);
}

static int	ft_set_path_after(char **path_after, int end)
{
	char	*temp_elem;

	temp_elem = ft_substr(*path_after, end, ft_strlen(*path_after + end));
	if (temp_elem == NULL)
		return (EXIT_FAILURE);
	free(*path_after);
	*path_after = temp_elem;
	return (EXIT_SUCCESS);
}

int	ft_set_wildcard_name_path(char **path_after, char **wildcard_name,
	t_list *path_before, t_list **wildcard_bool_list)
{
	int		begin;
	int		end;
	char	*path_before_str;

	ft_set_begin_wildcard_name(path_after, &begin, &end, wildcard_bool_list);
	path_before_str = ft_substr(*path_after, 0, begin);
	if (path_before_str == NULL)
		return (EXIT_FAILURE);
	if (ft_add_to_path_before(path_before, path_before_str))
		return (EXIT_FAILURE);
	if ((*path_after)[end] == '\0')
	{
		free(*path_after);
		*path_after = NULL;
		return (EXIT_SUCCESS);
	}
	end = begin;
	while ((*path_after)[end] != '\0' && (*path_after)[end] != '/')
		end++;
	*wildcard_name = ft_substr(*path_after, begin, end - begin);
	if (*wildcard_name == NULL)
		return (EXIT_FAILURE);
	if (ft_set_path_after(path_after, end))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
