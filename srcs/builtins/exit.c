/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npremont <npremont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 10:36:00 by npremont          #+#    #+#             */
/*   Updated: 2024/03/12 13:34:37 by npremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_exit(t_list **en, t_bool is_child)
{
	ft_envclear(en, free_globvar);
	rl_clear_history();
	if (is_child == false)
		if (write(1, "exit\n", 5) == -1)
			return (EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}
