/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_wildcard_value.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 02:07:40 by lethomas          #+#    #+#             */
/*   Updated: 2024/03/07 14:13:17 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_add_entry_if_wildcard_cmp(char *wildcard_name,
	t_list **wildcard_value_list, DIR *dir_flow, t_list *wildcard_bool_list)
{
	char			*name_in_dir;
	t_list			*list_elem;
	struct dirent	*file_in_dir;

	file_in_dir = readdir(dir_flow);
	if (file_in_dir == NULL)
		return (BREAK);
	name_in_dir = file_in_dir->d_name;
	if (name_in_dir[0] == '.')
		return (EXIT_SUCCESS);
	if (ft_wildcard_cmp(wildcard_name, name_in_dir, wildcard_bool_list)
		== false)
		return (EXIT_SUCCESS);
	name_in_dir = ft_strdup(name_in_dir);
	if (name_in_dir == NULL)
		return (EXIT_FAILURE);
	list_elem = ft_lstnew(name_in_dir);
	if (list_elem == NULL)
		return (EXIT_FAILURE);
	ft_lstadd_back(wildcard_value_list, list_elem);
	return (EXIT_SUCCESS);
}

static int	ft_get_new_entry(char *wildcard_name, t_list **wildcard_value_list,
	char *dir_path, t_list *wildcard_bool_list)
{
	DIR	*dir_flow;
	int	return_value;

	return_value = EXIT_SUCCESS;
	if (dir_path[0] == '\0')
		dir_flow = opendir("./");
	else
		dir_flow = opendir(dir_path);
	if (dir_flow == NULL)
		return (EXIT_SUCCESS);
	while (return_value != BREAK)
	{
		return_value = ft_add_entry_if_wildcard_cmp(wildcard_name,
				wildcard_value_list, dir_flow, wildcard_bool_list);
		if (return_value == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	if (closedir(dir_flow))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
//differencier l erreur et l absence de dir avec errno

static int	ft_add_new_entry_to_path_before(char *wildcard_name,
	t_list **wildcard_bool_list, t_list **path_before)
{
	t_list	*wildcard_value_list;
	t_list	*temp_elem;

	temp_elem = NULL;
	while (*path_before != NULL)
	{
		wildcard_value_list = NULL;
		if (ft_get_new_entry(wildcard_name, &wildcard_value_list,
				(char *)(*path_before)->content, *wildcard_bool_list))
			return (EXIT_FAILURE);
		if (temp_elem == NULL && wildcard_value_list != NULL)
			temp_elem = wildcard_value_list;
		if (ft_update_path_before(path_before, wildcard_value_list))
			return (EXIT_FAILURE);
	}
	*path_before = temp_elem;
	return (EXIT_SUCCESS);
}

static int	ft_init_path_before_after(t_list **path_before, char **path_after,
	char *wildcard_path)
{
	char	*content;

	content = ft_strdup("");
	if (content == NULL)
		return (EXIT_FAILURE);
	*path_before = ft_lstnew(content);
	if (*path_before == NULL)
		return (EXIT_FAILURE);
	*path_after = ft_strdup(wildcard_path);
	if (*path_after == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_get_wildcard_value(char *wildcard_path, t_list **wildcard_bool_list,
	t_list **path_before)
{
	char	*wildcard_name;
	char	*path_after;

	if (ft_init_path_before_after(path_before, &path_after, wildcard_path))
		return (EXIT_FAILURE);
	while (*path_before != NULL)
	{
		if (ft_set_wildcard_name_path(&path_after, &wildcard_name,
				*path_before, wildcard_bool_list))
			return (EXIT_FAILURE);
		if (path_after == NULL)
			return (EXIT_SUCCESS);
		if (ft_add_new_entry_to_path_before(wildcard_name,
				wildcard_bool_list, path_before))
			return (EXIT_FAILURE);
		ft_update_wildcard_bool_list_old_entry(wildcard_name,
			wildcard_bool_list);
		free(wildcard_name);
	}
	return (EXIT_SUCCESS);
}
