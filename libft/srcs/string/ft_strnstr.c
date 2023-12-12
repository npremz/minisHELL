/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 17:21:01 by lethomas          #+#    #+#             */
/*   Updated: 2023/11/27 19:26:38 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	i2;
	size_t	needle_len;

	i = 0;
	needle_len = ft_strlen (needle);
	if (!needle_len)
		return ((char *)haystack);
	while (haystack[i] && i < len)
	{
		i2 = 0;
		while (haystack[i + i2] == needle[i2] && i2 < needle_len)
			i2++;
		if (i2 == needle_len && i + i2 <= len)
			return (&((char *)haystack)[i]);
		i++;
	}
	return (NULL);
}
