/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 17:16:55 by lethomas          #+#    #+#             */
/*   Updated: 2023/11/27 19:26:38 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

double	ft_atod(const char *str, char alpha_term_allow)
{
	int			sign;
	double		res;
	long int	power;

	sign = 1;
	res = 0;
	power = 10;
	while ((*str > 8 && *str < 14) || *str == ' ')
		str++;
	if (*str == '+' || *str == '-')
		if (*(str++) == '-')
			sign = -1;
	while (*str >= '0' && *str <= '9')
		res = 10 * res + sign * (*(str++) - '0');
	if (*str == '.')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		res += (double)(sign * (*(str++) - '0')) / (double)(power);
		power *= power;
	}
	if (!alpha_term_allow && *str != 0)
		return ((double)INT_MAX);
	return (res);
}
