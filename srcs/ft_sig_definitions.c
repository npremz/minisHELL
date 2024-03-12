/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sig_definitions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npremont <npremont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:45:23 by npremont          #+#    #+#             */
/*   Updated: 2024/03/12 16:52:13 by npremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_define_ctrl_c(void)
{
	struct sigaction	sa;

	sa.sa_handler = ft_new_prompt;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		write(2, "minishell: signals init failed.\n", 33);
		exit(EXIT_FAILURE);
	}

}

void	ft_define_ctrl_bs(void)
{
	struct sigaction	sa;

	sa.sa_handler = ft_null;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
	{
		write(2, "minishell: signals init failed.\n", 33);
		exit(EXIT_FAILURE);
	}
}
