/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npremont <npremont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 09:39:49 by npremont          #+#    #+#             */
/*   Updated: 2023/11/06 11:47:47 by npremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_gnl(char *prefix, char *suffix, int has_fail)
{
	char			*str;
	unsigned long	str_size;
	int				i;

	str_size = ft_strlen(prefix) + ft_strlen(suffix);
	str = malloc((str_size + 1) * sizeof(char));
	if (str == NULL)
		return (free(prefix), NULL);
	if (suffix == NULL || prefix == NULL || has_fail == -1)
		return (free(prefix), ft_free_gnl(&suffix, 1, NULL), free(str), NULL);
	i = 0;
	while (prefix[i] != '\0')
	{
		*str = prefix[i++];
		str++;
	}
	i = 0;
	while (suffix[i] != '\0')
	{
		*str = suffix[i++];
		str++;
	}
	*str = '\0';
	return (free(prefix), str - str_size);
}

int	ft_has_newline(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		++i;
	}
	return (0);
}

void	ft_free_gnl(char **ptr, int flag, char **buff)
{
	if (flag == 1)
	{
		free(*ptr);
		*ptr = NULL;
	}
	else
	{
		if (*ptr == NULL)
		{
			free(*buff);
			*buff = NULL;
		}
	}
}
