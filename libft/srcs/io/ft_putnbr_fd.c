/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 11:07:41 by lethomas          #+#    #+#             */
/*   Updated: 2023/11/27 19:26:38 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static int	ft_putnbr_sub(int nb, int sign, int fd)
{
	if (nb / 10)
		if (ft_putnbr_sub (nb / 10, sign, fd))
			return (1);
	if (ft_putchar_fd ('0' + sign * (nb % 10), fd))
		return (1);
	return (0);
}

int	ft_putnbr_fd(int nb, int fd)
{
	int	sign;

	sign = 1;
	if (fd < 0)
		return (1);
	if (nb < 0)
	{
		sign = -1;
		if (ft_putchar_fd ('-', fd))
			return (1);
	}
	if (ft_putnbr_sub (nb, sign, fd))
		return (1);
	return (0);
}
