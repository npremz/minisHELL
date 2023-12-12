/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_enum_libft.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 02:07:00 by lethomas          #+#    #+#             */
/*   Updated: 2023/12/10 02:13:25 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_ENUM_LIBFT_H
# define STRUCT_ENUM_LIBFT_H

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef enum e_bool
{
	false,
	true
}	t_bool;

typedef enum e_parity
{
	even,
	odd
}	t_parity;

typedef enum e_sign
{
	positive,
	negative
}	t_sign;

#endif
