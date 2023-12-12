/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 12:57:51 by lethomas          #+#    #+#             */
/*   Updated: 2023/11/27 19:26:38 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

int	ft_printf(const char *str, ...)
{
	int		nb_chr;
	va_list	lst_arg;
	int		tab_flag[8];

	nb_chr = 0;
	va_start (lst_arg, str);
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			ft_bzero ((void *)tab_flag, 8 * sizeof (int));
			if (ft_conversion (&nb_chr, lst_arg, &str, tab_flag))
				return (va_end (lst_arg), -1);
		}
		else
			if (++nb_chr && ft_putchar_fd (*str, 1))
				return (va_end (lst_arg), -1);
		str++;
	}
	va_end (lst_arg);
	return (nb_chr);
}
