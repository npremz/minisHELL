/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 14:13:31 by lethomas          #+#    #+#             */
/*   Updated: 2023/11/30 10:29:10 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static void	ft_free_all(char **line, char **buffer)
{
	if (line)
	{
		free (*line);
		*line = NULL;
	}
	if (buffer)
	{
		free (*buffer);
		*buffer = NULL;
	}
}

static int	ft_modify_bufferwithremaining(char **buffer)
{
	size_t	offset;
	size_t	buffer_size;
	char	*buffer_temp;

	offset = 0;
	buffer_size = ft_strlen (*buffer) + 1;
	while ((*buffer)[offset] != '\n' && (*buffer)[offset] != 0)
		offset++;
	offset += ((*buffer)[offset] == '\n');
	buffer_temp = (char *)malloc(sizeof (char) * (buffer_size - offset));
	if (!buffer_temp)
		return (1);
	ft_strlcpy (buffer_temp, *buffer + offset, buffer_size - offset);
	ft_free_all (NULL, buffer);
	*buffer = buffer_temp;
	return (0);
}

static int	ft_fill_line_set_continue(char *buffer, char **line, char *bool_v)
{
	char	*line_temp;
	char	chr_temp;
	size_t	len;

	len = 0;
	while (buffer[len] != '\n' && buffer[len] != 0)
		len++;
	*bool_v = !(buffer[len] == '\n');
	chr_temp = buffer[len + (buffer[len] == '\n')];
	buffer[len + (buffer[len] == '\n')] = 0;
	line_temp = ft_strjoin (*line, buffer, 0, 0);
	if (!line_temp)
		return (1);
	buffer[len + (buffer[len] == '\n')] = chr_temp;
	ft_free_all (line, NULL);
	*line = line_temp;
	return (0);
}

static int	ft_create_emptyline_bufferfromremaining(int *nbyte_read,
	char **buffer, char **line)
{
	char	*buffer_temp;

	buffer_temp = NULL;
	*nbyte_read = 0;
	*line = NULL;
	*line = (char *)ft_calloc (1, sizeof (char));
	if (!*line)
		return (1);
	buffer_temp = (char *)malloc(((unsigned long)BUFFER_SIZE + 1)
			* sizeof (char));
	if (!buffer_temp)
		return (1);
	buffer_temp[0] = 0;
	if (*buffer)
		ft_strlcpy (buffer_temp, *buffer, (unsigned long)BUFFER_SIZE + 1);
	ft_free_all (NULL, buffer);
	*buffer = buffer_temp;
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*buffer[OPEN_MAX];
	char		*line;
	char		continue_to_read;
	int			nbyte;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= OPEN_MAX)
		return (NULL);
	if (ft_create_emptyline_bufferfromremaining(&nbyte, buffer + fd, &line))
		return (ft_free_all (buffer + fd, &line), NULL);
	if (ft_fill_line_set_continue (buffer[fd], &line, &continue_to_read))
		return (ft_free_all (buffer + fd, &line), NULL);
	while (continue_to_read)
	{
		nbyte = read (fd, buffer[fd], BUFFER_SIZE);
		if (nbyte <= 0)
			break ;
		buffer[fd][nbyte] = 0;
		if (ft_fill_line_set_continue (buffer[fd], &line, &continue_to_read))
			return (ft_free_all (buffer + fd, &line), NULL);
	}
	if (ft_modify_bufferwithremaining (buffer + fd))
		return (ft_free_all (buffer + fd, &line), NULL);
	if (line[0] == 0 || nbyte < 0)
		return (ft_free_all (buffer + fd, &line), NULL);
	return (line);
}
