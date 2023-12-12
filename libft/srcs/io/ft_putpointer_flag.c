/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putpointer_flag.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 18:03:39 by lethomas          #+#    #+#             */
/*   Updated: 2023/11/27 19:20:29 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

static int	ft_pointer_nb_digit(unsigned long int nb)
{
	int		len;

	len = 0;
	if (!nb)
		return (1);
	while (nb && ++len)
		nb /= 16;
	return (len);
}

static void	ft_pointer_set_precision_sign_width(unsigned long int nb,
	int *tab_flag)
{
	int		len;

	len = ft_pointer_nb_digit (nb);
	if (tab_flag[PRECISION] - len > 0)
	{
		tab_flag[PRECISION] -= len;
		len += tab_flag[PRECISION];
	}
	else
		tab_flag[PRECISION] = 0;
	if (tab_flag[WIDTH] - len - 2 > 0)
		tab_flag[WIDTH] -= (len - 2);
	else
		tab_flag[WIDTH] = 0;
}

static int	ft_putpointer(unsigned long int nb)
{
	if (nb / 16)
		if (ft_putpointer(nb / 16))
			return (1);
	if (nb % 16 < 10)
		if (ft_putchar_fd (48 + nb % 16, 1))
			return (1);
	if (nb % 16 >= 10)
		if (ft_putchar_fd (87 + nb % 16, 1))
			return (1);
	return (0);
}

int	ft_putpointer_flag(int *nb_chr, unsigned long int nb, int *tab_flag)
{
	ft_pointer_set_precision_sign_width (nb, tab_flag);
	while (!tab_flag[MINUS] && tab_flag[WIDTH] && tab_flag[WIDTH]--
		&& ++(*nb_chr))
		if (ft_putchar_fd (' ', 1))
			return (1);
	if (ft_putstr_fd ("0x", 1))
		return (1);
	(*nb_chr) += 2;
	while (!tab_flag[MINUS] && tab_flag[WIDTH] && tab_flag[WIDTH]--
		&& ++(*nb_chr))
		if (ft_putchar_fd ('0', 1))
			return (1);
	if (ft_putpointer (nb))
		return (1);
	*nb_chr += ft_pointer_nb_digit (nb);
	while (tab_flag[MINUS] && tab_flag[WIDTH]-- && ++(*nb_chr))
		if (ft_putchar_fd (' ', 1))
			return (1);
	return (0);
}
