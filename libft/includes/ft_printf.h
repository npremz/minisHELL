/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 15:42:55 by lethomas          #+#    #+#             */
/*   Updated: 2023/10/25 15:23:21 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "libft.h"

# define WIDTH 0
# define PRECISION 1
# define MINUS 2
# define PLUS 3
# define ZERO 4
# define SPACE 5
# define HASH 6
# define DOT 7
# define SIGNED 0
# define UNSIGNED 1

int		ft_conversion(int *nb_chr, va_list lst_arg, const char **str,
			int *tab_flag);
int		ft_setflag(int *nb_chr, va_list lst_arg, const char **str,
			int *tab_flag);
int		ft_putnbr_flag(int *nb_chr, long int nb, int *tab_flag, char info);
int		ft_putstr_flag(int *nb_chr, const char *str, int *tab_flag, char info);
int		ft_putpointer_flag(int *nb_chr, unsigned long int nb, int *tab_flag);

#endif