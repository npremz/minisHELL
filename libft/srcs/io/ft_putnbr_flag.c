/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_flag.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 12:58:00 by lethomas          #+#    #+#             */
/*   Updated: 2023/11/27 19:20:42 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

static int	ft_nb_digit(long int nb, int base)
{
	int		len;

	len = 0;
	if (!nb)
		return (1);
	while (nb && ++len)
		nb /= base;
	return (len);
}

static char	ft_set_precision_sign_width(long int nb, int *tab_flag, char info,
	int *base)
{
	int		len;
	char	sign;

	*base = 10 * (info == 'd' || info == 'u' || info == 'i')
		+ 16 * (info == 'x' || info == 'X');
	len = ft_nb_digit (nb, *base);
	if (tab_flag[PRECISION] - len > 0)
	{
		tab_flag[PRECISION] -= len;
		len += tab_flag[PRECISION];
	}
	else
		tab_flag[PRECISION] = 0;
	sign = '-' * (nb < 0) + '+' * (tab_flag[PLUS] && nb >= 0)
		+ ' ' * (tab_flag[SPACE] && nb >= 0);
	if (sign)
		len++;
	if (tab_flag[WIDTH] - len - 2 * ((info == 'x' || info == 'X')
			&& tab_flag[HASH]) > 0)
		tab_flag[WIDTH] -= len + 2 * ((info == 'x' || info == 'X')
				&& tab_flag[HASH]);
	else
		tab_flag[WIDTH] = 0;
	return (sign);
}

static int	ft_putnbr_base(long int nb, int base, char sign, char info)
{
	if (nb / base)
		if (ft_putnbr_base(nb / base, base, sign, info))
			return (1);
	if (sign * (nb % base) < 10)
		if (ft_putchar_fd (48 + sign * (nb % base), 1))
			return (1);
	if (sign * (nb % base) >= 10)
		if (ft_putchar_fd (87 + sign * (nb % base) - 32 * info, 1))
			return (1);
	return (0);
}

static int	ft_putbefore_nbr_flag(int *nb_chr, int sign, int *tab_flag,
	char info)
{
	while (!tab_flag[MINUS] && !(tab_flag[ZERO] && !tab_flag[DOT])
		&& tab_flag[WIDTH] && tab_flag[WIDTH]-- && ++(*nb_chr))
		if (ft_putchar_fd (' ', 1))
			return (1);
	if (tab_flag[HASH] && info == 'X' && ++(*nb_chr) && ++(*nb_chr))
		if (ft_putstr_fd ("0X", 1))
			return (1);
	if (tab_flag[HASH] && info == 'x' && ++(*nb_chr) && ++(*nb_chr))
		if (ft_putstr_fd ("0x", 1))
			return (1);
	if (sign && ++(*nb_chr))
		if (ft_putchar_fd (sign, 1))
			return (1);
	while (!tab_flag[MINUS] && tab_flag[ZERO] && tab_flag[WIDTH]
		&& !tab_flag[DOT] && tab_flag[WIDTH]-- && ++(*nb_chr))
		if (ft_putchar_fd ('0', 1))
			return (1);
	while (tab_flag[PRECISION]-- && ++(*nb_chr))
		if (ft_putchar_fd ('0', 1))
			return (1);
	return (0);
}

int	ft_putnbr_flag(int *nb_chr, long int nb, int *tab_flag, char info)
{
	char	sign;
	int		base;

	sign = ft_set_precision_sign_width (nb, tab_flag, info, &base);
	if (ft_putbefore_nbr_flag (nb_chr, sign, tab_flag, info))
		return (1);
	if (ft_putnbr_base (nb, base, 1 - 2 * (sign == '-'), (info == 'X')))
		return (1);
	*nb_chr += ft_nb_digit (nb, base);
	while (tab_flag[MINUS] && tab_flag[WIDTH]-- && ++(*nb_chr))
		if (ft_putchar_fd (' ', 1))
			return (1);
	return (0);
}
