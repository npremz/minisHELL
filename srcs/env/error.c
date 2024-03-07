/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npremont <npremont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:03:49 by npremont          #+#    #+#             */
/*   Updated: 2024/03/05 11:28:08 by npremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_error(char *str)
{
	write(2, str, ft_strlen(str));
}

void	exit_error(char *str, t_list **en, t_globvar *var, int code)
{
	if (str)
		print_error(str);
	if (en)
		ft_envclear(en, &free_globvar);
	if (var)
		ft_free((void **)(&var));
	exit(code);
}
