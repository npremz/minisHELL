/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 11:15:27 by lethomas          #+#    #+#             */
/*   Updated: 2023/12/08 18:14:38 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static void	ft_free_strjoin(char *f_str, char *s_str, t_bool free_f,
	t_bool free_s)
{
	if (free_f == true)
		free (f_str);
	if (free_s == true)
		free (s_str);
}

char	*ft_strjoin(char *f_str, char *s_str, t_bool free_f, t_bool free_s)
{
	int		n_str_len;
	char	*n_str;

	if (!f_str || !s_str)
		return (ft_free_strjoin(f_str, s_str, free_f, free_s), NULL);
	n_str_len = ft_strlen (f_str) + ft_strlen (s_str);
	n_str = (char *)malloc (sizeof (char) * (n_str_len + 1));
	if (!n_str)
		return (ft_free_strjoin(f_str, s_str, free_f, free_s), NULL);
	n_str[0] = 0;
	ft_strlcat (n_str, f_str, n_str_len + 1);
	ft_strlcat (n_str, s_str, n_str_len + 1);
	ft_free_strjoin(f_str, s_str, free_f, free_s);
	return (n_str);
}
