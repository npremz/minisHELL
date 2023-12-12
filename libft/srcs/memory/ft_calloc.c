/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 11:04:14 by lethomas          #+#    #+#             */
/*   Updated: 2023/11/27 19:24:12 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*pt;

	if ((size && count > SIZE_MAX / size))
		return (NULL);
	pt = malloc (count * size);
	if (!pt)
		return (NULL);
	ft_bzero (pt, count * size);
	return (pt);
}
