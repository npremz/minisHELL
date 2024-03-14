/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npremont <npremont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 10:36:00 by npremont          #+#    #+#             */
/*   Updated: 2024/03/14 18:49:25 by npremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_atol(const char *str)
{
	int			sign;
	long int	res;

	sign = 1;
	res = 0;
	while ((*str > 8 && *str < 14) || *str == ' ')
		str++;
	if (*str == '+' || *str == '-')
		if (*(str++) == '-')
			sign = -1;
	while (*str >= '0' && *str <= '9')
	{
		res = 10 * res + sign * (*(str++) - '0');
	}
	return (res);
}

int	arg_is_valid(char *arg)
{
	int	i;
	int	neg;

	neg = 0;
	if (arg[0] == '-')
	{
		arg++;
		neg = 1;
	}
	if (ft_strlen(arg) > 19)
		return (0);
	i = -1;
	while (arg[++i])
		if (!ft_isdigit(arg[i]))
			return (0);
	if (neg == 0)
	{
		if (ft_strncmp(arg, "9223372036854775807", 20) > 0)
			return (-1);
	}
	else
		if (ft_strncmp(arg, "9223372036854775808", 20) > 0)
			return (-1);
	return (1);
}

int	ft_exit(t_list **en, char **args, t_bool is_child)
{
	if (is_child == false)
		if (write(1, "exit\n", 5) == -1)
			return (EXIT_FAILURE);
	ft_envclear(en, free_globvar);
	rl_clear_history();
	if (args && args[1] && arg_is_valid(args[1]) <= 0)
	{
		write(2, "minishell: exit: ", 18);
		write(2, args[1], ft_strlen(args[1]));
		write(2, ": numeric argument required\n", 29);
		if (!args[2] && arg_is_valid(args[1]) == -1)
			exit(255);
	}
	else if (args && args[1] && !args[2])
		exit((unsigned char)ft_atol(args[1]));
	else if (args && args[1] && args[2])
	{
		write(2, "minishell: exit: too many arguments\n", 37);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
