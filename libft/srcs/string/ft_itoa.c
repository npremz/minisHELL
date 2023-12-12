/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 11:05:10 by lethomas          #+#    #+#             */
/*   Updated: 2023/11/27 19:26:38 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static int	ft_str_construct(int n, int *nb_digit, char **str_n, int sign)
{
	(*nb_digit)++;
	if (n / 10)
	{
		if (ft_str_construct (n / 10, nb_digit, str_n, sign))
			return (1);
	}
	else
	{
		*str_n = (char *)malloc (sizeof (char) * (*nb_digit + 1));
		if (!*str_n)
			return (1);
		(*str_n)[*nb_digit] = 0;
		*nb_digit = 0;
		if (sign == -1 && ++(*nb_digit))
			(*str_n)[0] = '-';
	}
	(*str_n)[(*nb_digit)++] = 48 + sign * (n % 10);
	return (0);
}

char	*ft_itoa(int n)
{
	int		nb_digit;
	int		sign;
	char	*str_n;

	nb_digit = 0;
	sign = 1;
	if (n < 0 && ++nb_digit)
		sign = -1;
	if (ft_str_construct (n, &nb_digit, &str_n, sign))
		return (NULL);
	return (str_n);
}
