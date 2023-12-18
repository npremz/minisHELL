/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_wildcard_value.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 02:07:40 by lethomas          #+#    #+#             */
/*   Updated: 2023/12/17 00:03:33 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing_exec.h"

static int	ft_set_wildcard_name_path(char *wildcard_path, char **wildcard_name,
	char **path_before, char **path_after, t_list *wildcard_list)
{
	int	begin;
	int	end;

	begin = 0;
	end = 0;
	ft_set_end(wildcard_path, wildcard_list, &end);
	while (end != 0 && wildcard_path[end] != '/')
		end--;
	if (end == 0 && wildcard_path[end] != '/')
		*path_before = ft_strdup("./");
	else
		*path_before = ft_substr(wildcard_path, 0, end + 1);
	if (*path_before == NULL)
		return (EXIT_FAILURE);
	end += (wildcard_path[end] == '/');
	begin = end;
	while (wildcard_path[end] != '\0' && wildcard_path[end] != '/')
		end++;
	*wildcard_name = ft_substr(wildcard_path, begin, end - begin);
	if (*wildcard_name == NULL)
		return (EXIT_FAILURE);
	begin = end;
	if (wildcard_path[end] == '\0')
		*path_after = ft_strdup("");
	else
		*path_after = ft_substr(wildcard_path, begin,
				ft_strlen(wildcard_path + begin));
	if (*path_after == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	ft_set_wildcard_value_path(t_list *wildcard_value_list,
	char *path_before, char *path_after)
{
	while (wildcard_value_list != NULL)
	{
		wildcard_value_list->content = (void *)ft_strjoin(path_before,
				wildcard_value_list->content, false, true);
		if (wildcard_value_list->content == NULL)
			return (EXIT_FAILURE);
		wildcard_value_list->content
			= (void *)ft_strjoin(wildcard_value_list->content, path_after,
				true, false);
		if (wildcard_value_list->content == NULL)
			return (EXIT_FAILURE);
		wildcard_value_list = wildcard_value_list->next;
	}
	free(path_before);
	free(path_after);
	return (EXIT_SUCCESS);
}

static int	ft_set_wildcard_value_list(char *wildcard_name,
	t_list **wildcard_value_list, DIR *dir_flow, t_list *wildcard_list)
{
	char			*name_in_dir;
	t_list			*list_elem;
	struct dirent	*file_in_dir;

	while (true)
	{
		file_in_dir = readdir(dir_flow);
		if (file_in_dir == NULL)
			break ;
		name_in_dir = file_in_dir->d_name;
		if (ft_wildcard_cmp(wildcard_name, name_in_dir, wildcard_list)
			== false)
			continue ;
		name_in_dir = ft_strdup(name_in_dir);
		if (name_in_dir == NULL)
			return (EXIT_FAILURE);
		list_elem = ft_lstnew(name_in_dir);
		if (list_elem == NULL)
			return (EXIT_FAILURE);
		ft_lstadd_back(wildcard_value_list, list_elem);
	}
	return (EXIT_SUCCESS);
}

static void	ft_delete_wildcard_list_effective_elem(char	*wildcard_name,
	t_list **wildcard_list)
{
	int		i;
	t_list	*elem_list;
	t_list	*new_begin;

	i = 0;
	new_begin = *wildcard_list;
	while (wildcard_name[i] != '\0')
	{
		if (wildcard_name[i] == '*')
		{
			elem_list = (*wildcard_list)->next;
			if ((*wildcard_list)->prev != NULL)
				(*wildcard_list)->prev->next = (*wildcard_list)->next;
			if ((*wildcard_list)->next != NULL)
				(*wildcard_list)->next->prev = (*wildcard_list)->prev;
			if (*wildcard_list == new_begin)
				new_begin = (*wildcard_list)->next;
			free((*wildcard_list)->content);
			free(*wildcard_list);
			*wildcard_list = elem_list;
		}
		i++;
	}
	*wildcard_list = new_begin;
}

t_list	*ft_get_wildcard_value(char *wildcard_path, t_list **wildcard_list)
{
	char	*wildcard_name;
	char	*path_before;
	char	*path_after;
	t_list	*wildcard_value_list;
	DIR		*dir_flow;

	wildcard_value_list = NULL;
	if (ft_set_wildcard_name_path(wildcard_path, &wildcard_name, &path_before,
			&path_after, *wildcard_list))
		return (NULL);
	dir_flow = opendir(path_before);
	if (dir_flow == NULL)
		return (NULL);
	if (ft_set_wildcard_value_list(wildcard_name, &wildcard_value_list,
			dir_flow, *wildcard_list))
		return (NULL);
	if (ft_set_wildcard_value_path(wildcard_value_list, path_before,
			path_after))
		return (NULL);
	ft_delete_wildcard_list_effective_elem(wildcard_name, wildcard_list);
	free(wildcard_name);
	if (closedir(dir_flow))
		return (NULL);
	return (wildcard_value_list);
}
//
// int main(void)
// {
// 	char str[]= "./sr*/ft_*list.c";
// 	int *a = malloc(4);
// 	*a = 1;
// 	t_list *list = &(t_list){a, 0, 0};
// 	t_list *list_sol = ft_get_wildcard_value(str, &list);
// 	if (list_sol == NULL)
// 		return (EXIT_FAILURE);
// 	while (list_sol != NULL)
// 	{
// 		printf("%s\n", (char *)list_sol->content);
// 		list_sol = list_sol->next;
// 	}
// 	printf("%p\n", list);
// 	return (EXIT_SUCCESS);
// }
