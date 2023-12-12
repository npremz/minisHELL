/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 11:24:24 by lethomas          #+#    #+#             */
/*   Updated: 2023/11/27 19:26:38 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*new_s;

	if (!s || !f)
		return (NULL);
	i = 0;
	new_s = (char *)malloc (sizeof (char) * (ft_strlen (s) + 1));
	if (!new_s)
		return (NULL);
	while (*s)
	{
		new_s[i] = (*f)(i, *(s++));
		i++;
	}
	new_s[i] = 0;
	return (new_s);
}
