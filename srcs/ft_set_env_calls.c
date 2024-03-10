/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_env_calls.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npremont <npremont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 22:10:33 by npremont          #+#    #+#             */
/*   Updated: 2024/03/10 23:16:23 by npremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_set_env_calls(t_cmd *cmd)
{
	if (ft_handle_name(cmd))
		return (EXIT_FAILURE);
	if (ft_handle_args(cmd))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
