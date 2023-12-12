/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setflag.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 12:58:14 by lethomas          #+#    #+#             */
/*   Updated: 2023/11/27 19:26:38 by lethomas         ###   ########.fr       */
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

static void	ft_set_width_precision(int info, const char **str, int *tab_flag)
{
	tab_flag[info] = ft_atoi (*str, 1);
	*str += ft_nb_digit ((long int)tab_flag[info], 10);
	if (info == PRECISION && !tab_flag[PRECISION])
		(*str)--;
}

int	ft_setflag(int *nb_chr, va_list lst_arg, const char **str, int *tab_flag)
{
	if (**str != '0' && ft_isdigit (**str))
		ft_set_width_precision(WIDTH, str, tab_flag);
	else if (**str == '.' && ++(tab_flag[DOT]) && ++(*str))
	{
		while (**str == '0')
			(*str)++;
		ft_set_width_precision(PRECISION, str, tab_flag);
	}
	else if (**str == '-' && *((*str)++))
		tab_flag[MINUS] = 1;
	else if (**str == '+' && *((*str)++))
		tab_flag[PLUS] = 1;
	else if (**str == '0' && *((*str)++))
		tab_flag[ZERO] = 1;
	else if (**str == ' ' && *((*str)++))
		tab_flag[SPACE] = 1;
	else if (**str == '#' && *((*str)++))
		tab_flag[HASH] = 1;
	else
		return (1);
	if (ft_conversion (nb_chr, lst_arg, str, tab_flag))
		return (1);
	return (0);
}

// int	ft_check_symb_apostrophe(char symb, const char *str)
// {
// 	if (symb == '\'')
// 	{
// 		if (*(str + 1) == symb)
// 		{
// 			if (*(str + 2) == '\'')
// 			{
// 				str += 3;
// 				return (1);
// 			}
// 		}
// 	}
// 	return (0);
// }
