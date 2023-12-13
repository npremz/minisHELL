/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npremont <npremont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 09:39:43 by npremont          #+#    #+#             */
/*   Updated: 2023/11/06 11:41:44 by npremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_get_after(char *str)
{
	char	*res;
	int		i;

	if (str == NULL)
		return (NULL);
	res = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!res)
		return (NULL);
	while (*str != '\n' && *str)
		++str;
	if (*str == '\n')
		++str;
	i = 0;
	while (str[i] != '\0')
	{
		res[i] = str[i];
		++i;
	}
	res[i] = '\0';
	return (res);
}

static char	*ft_get_before(char *str)
{
	char	*res;
	int		i;

	if (str == NULL)
		return (NULL);
	res = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (str[i] != '\n' && str[i])
	{
		res[i] = str[i];
		++i;
	}
	if (str[i] == '\n')
		res[i++] = '\n';
	res[i] = '\0';
	return (res);
}

static char	*ft_h_endline(char **stash, char *buff, int has_fail)
{
	char	*before_newline;
	char	*after_newline;

	if (has_fail == -1)
		return (ft_free_gnl(&buff, 1, NULL), NULL);
	before_newline = ft_get_before(buff);
	after_newline = ft_get_after(buff);
	if (!after_newline)
		return (free(before_newline), ft_free_gnl(&buff, 1, NULL),
			ft_free_gnl(stash, 1, NULL), NULL);
	if (!before_newline)
		return (free(after_newline), ft_free_gnl(&buff, 1, NULL),
			ft_free_gnl(stash, 1, NULL), NULL);
	*stash = ft_strjoin_gnl(*stash, before_newline, has_fail);
	free(before_newline);
	ft_free_gnl(&buff, 1, NULL);
	return (after_newline);
}

static char	*ft_read(char *stash, char **buff, int fd)
{
	int		r_bytes;

	if (*buff == NULL)
		return (free(stash), NULL);
	while (ft_has_newline(stash) == 0 && stash != NULL)
	{
		r_bytes = read(fd, *buff, BUFFER_SIZE);
		(*buff)[r_bytes] = '\0';
		if (r_bytes > 0)
		{
			if (ft_has_newline(*buff) == 0)
				stash = ft_strjoin_gnl(stash, *buff, r_bytes);
			else
				*buff = ft_h_endline(&stash, *buff, r_bytes);
		}
		else
		{
			if (stash[0] == '\0')
				return (ft_free_gnl(buff, 1, NULL), free(stash), NULL);
			return (stash);
		}
	}
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*buff[OPEN_MAX];
	char		*stash;

	if (fd < 0 || read(fd, 0, 0) == -1 || BUFFER_SIZE <= 0 || fd >= OPEN_MAX)
		return (ft_free_gnl(&buff[fd], 1, NULL), NULL);
	stash = ft_calloc(1, sizeof(char));
	if (!stash)
		return (ft_free_gnl(&buff[fd], 1, NULL), NULL);
	if (buff[fd] == NULL)
	{
		buff[fd] = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		stash = ft_read(stash, &buff[fd], fd);
	}
	else
	{
		if (ft_has_newline(buff[fd]))
			buff[fd] = ft_h_endline(&stash, buff[fd], 1);
		else
		{
			stash = ft_strjoin_gnl(stash, buff[fd], 1);
			stash = ft_read(stash, &buff[fd], fd);
		}
	}
	ft_free_gnl(&stash, 2, &buff[fd]);
	return (stash);
}
