/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 11:11:54 by lethomas          #+#    #+#             */
/*   Updated: 2023/11/24 18:23:26 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strdup(const char *src)
{
	size_t	src_len;
	char	*dst;

	src_len = ft_strlen (src);
	dst = (char *)malloc (sizeof (char) * (src_len + 1));
	if (!dst)
		return (NULL);
	ft_strlcpy (dst, src, src_len + 1);
	return (dst);
}
