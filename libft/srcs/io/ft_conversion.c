/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conversion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 12:57:43 by lethomas          #+#    #+#             */
/*   Updated: 2023/11/27 19:26:38 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

int	ft_conversion(int *nb_chr, va_list lst_arg, const char **str, int *tab_flag)
{
	if (**str == '%')
		return (ft_putstr_flag (nb_chr, "%", tab_flag, **str));
	else if (**str == 'd' || **str == 'i')
		return (ft_putnbr_flag (nb_chr, (long int)va_arg (lst_arg, int),
				tab_flag, **str));
	else if (**str == 'u')
		return (ft_putnbr_flag (nb_chr, (long int)va_arg (lst_arg,
					unsigned int), tab_flag, **str));
	else if (**str == 'x' || **str == 'X')
		return (ft_putnbr_flag (nb_chr, (long int)va_arg (lst_arg,
					unsigned int), tab_flag, **str));
	else if (**str == 'p')
		return (ft_putpointer_flag (nb_chr, (unsigned long int)va_arg (lst_arg,
					void *), tab_flag));
	else if (**str == 'c')
		return (ft_putstr_flag (nb_chr, (char []){(char)va_arg (lst_arg,
					int), 0}, tab_flag, **str));
	else if (**str == 's')
		return (ft_putstr_flag (nb_chr, va_arg (lst_arg, char *), tab_flag,
				**str));
	else
		if (ft_setflag(nb_chr, lst_arg, str, tab_flag))
			return (1);
	return (0);
}
