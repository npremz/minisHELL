/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npremont <npremont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 16:57:33 by npremont          #+#    #+#             */
/*   Updated: 2023/11/21 16:58:26 by npremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_has_duplicate(char c, char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			count++;
		i++;
	}
	if (count > 1)
		return (1);
	else
		return (0);
}

static int	ft_basecheck(char *base)
{
	int	i;

	i = 0;
	if (ft_strlen(base) < 2)
		return (0);
	while (base[i] != '\0')
	{
		if (base[i] == '+' || base[i] == '-')
			return (0);
		i++;
	}
	i = 0;
	while (base[i] != '\0')
	{
		if (ft_has_duplicate(base[i], base) == 1)
			return (0);
		i++;
	}
	return (1);
}

static int	ft_index_check(char *base, char c)
{
	int	i;

	i = 0;
	while (base[i] != c && base[i] != '\0')
	{
		i++;
	}
	if (base[i] == c)
		return (i);
	return (-1);
}

int	ft_atoi_base(char *str, char *base)
{
	int	i;
	int	nbr;
	int	which_sign;
	int	baselen;

	if (ft_basecheck(base) == 0)
		return (0);
	baselen = ft_strlen(base);
	which_sign = 1;
	nbr = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			which_sign *= -1;
		i++;
	}
	while (str[i++] != '\0' && ft_index_check(base, str[i - 1]) != -1)
		nbr = nbr * baselen + ft_index_check(base, str[i - 1]);
	return (nbr * which_sign);
}
