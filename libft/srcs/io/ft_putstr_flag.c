/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_flag.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 12:58:07 by lethomas          #+#    #+#             */
/*   Updated: 2023/11/27 19:26:38 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

static int	ft_set_precision_width(const char *str, int *tab_flag)
{
	int	len;

	len = ft_strlen (str);
	if (tab_flag[DOT] && (tab_flag[WIDTH] > tab_flag[PRECISION]))
		tab_flag[WIDTH] -= tab_flag[PRECISION];
	else if (tab_flag[WIDTH] > len)
		tab_flag[WIDTH] -= len;
	else
		tab_flag[WIDTH] = 0;
	return (len);
}

int	ft_putstr_flag(int *nb_chr, const char *str, int *tab_flag, char info)
{
	int	len;

	if (!str)
		str = "(null)";
	len = ft_set_precision_width (str, tab_flag);
	while (!tab_flag[MINUS] && tab_flag[WIDTH] && tab_flag[WIDTH]--)
		if (++(*nb_chr) && ft_putchar_fd (' ', 1))
			return (1);
	if (info == 'c' && *str == 0)
		if (++(*nb_chr) && ft_putchar_fd (0, 1))
			return (1);
	while (!tab_flag[DOT] && len && len--)
		if (++(*nb_chr) && ft_putchar_fd (*(str++), 1))
			return (1);
	while (len && len-- && tab_flag[PRECISION]--)
		if (++(*nb_chr) && ft_putchar_fd (*(str++), 1))
			return (1);
	while (tab_flag[WIDTH]--)
		if (++(*nb_chr) && ft_putchar_fd (' ', 1))
			return (1);
	return (0);
}
