/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 17:01:12 by lethomas          #+#    #+#             */
/*   Updated: 2023/11/27 13:28:54 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	ft_strncmp(const char *f_str, const char *s_str, int n)
{
	int	i;

	if (f_str == NULL || s_str == NULL || n < -1)
		return (0);
	i = 0;
	if (n == 0)
		return (0);
	if (n == -1)
		n = ft_strlen(f_str) + 1;
	while (f_str[i] == s_str[i] && f_str[i] && s_str[i] && i < n - 1)
		i++;
	return ((unsigned char)f_str[i] - (unsigned char)s_str[i]);
}
