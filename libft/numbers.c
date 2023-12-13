/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numbers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npremont <npremont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 11:27:16 by npremont          #+#    #+#             */
/*   Updated: 2023/11/06 12:00:07 by npremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printn(char *str)
{
	int		len;

	if (str == NULL)
		return (-1);
	else
	{
		len = ft_strlen(str);
		if (write(1, str, len) == -1)
		{
			free(str);
			return (-1);
		}
	}
	free (str);
	return (len);
}

int	ft_printaddr(char *str)
{
	int		len;

	if (str == NULL)
		return (-1);
	else
	{
		len = ft_strlen(str);
		if (write(1, "0x", 2) == -1)
		{
			free(str);
			return (-1);
		}
		if (write(1, str, len) == -1)
		{
			free(str);
			return (-1);
		}
	}
	free (str);
	return (len + 2);
}
