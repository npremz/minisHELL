/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 18:37:25 by lethomas          #+#    #+#             */
/*   Updated: 2023/11/27 19:19:45 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	ft_memcmp(const void *f_str, const void *s_str, size_t n)
{
	size_t	i;

	if (!n)
		return (0);
	i = 0;
	while (((unsigned char *)f_str)[i] == ((unsigned char *)s_str)[i]
			&& i < n - 1)
		i++;
	return (((unsigned char *)f_str)[i] - ((unsigned char *)s_str)[i]);
}
