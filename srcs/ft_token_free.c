/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 07:25:15 by lethomas          #+#    #+#             */
/*   Updated: 2023/12/10 07:25:52 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

void	ft_free_token(void *token)
{
	if (token == NULL)
		return ;
	free(((t_token *)token)->value);
	free(token);
}

void	ft_free_token_list(t_list **token_list)
{
	ft_lstclear(token_list, &ft_free_token);
}
