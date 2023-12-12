/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 11:09:03 by lethomas          #+#    #+#             */
/*   Updated: 2023/11/27 19:26:38 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static int	ft_create_word(int size_word, char **word, char const *str)
{
	int	i;

	i = 0;
	*word = (char *)malloc (sizeof (char) * (size_word + 1));
	if (!(*word))
		return (1);
	while (i < size_word)
		(*word)[i++] = *(str++);
	(*word)[i] = 0;
	return (0);
}

static int	ft_create_tab(int nb_word, char ***tab)
{
	*tab = (char **)malloc (sizeof (char *) * (nb_word + 1));
	if (!(*tab))
		return (1);
	(*tab)[nb_word] = 0;
	return (0);
}

static int	ft_split_recursive(char const *str, char c,
		int nb_word, char ***tab)
{
	char	*word;
	int		bool_l;
	int		size_word;

	word = NULL;
	bool_l = 0;
	size_word = 0;
	while (str[size_word] != c && str[size_word] != 0)
		size_word++;
	if (size_word > 0 && ++nb_word && ++bool_l)
		if (ft_create_word (size_word, &word, str))
			return (1);
	if (str[size_word])
		if (ft_split_recursive (&(str[size_word + 1]), c, nb_word, tab))
			return (free (word), 1);
	if (!str[size_word])
		if (ft_create_tab (nb_word, tab))
			return (free (word), 1);
	if (bool_l)
		(*tab)[nb_word - 1] = word;
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;

	if (!s)
		return (NULL);
	if (ft_split_recursive (s, c, 0, &tab))
		return (NULL);
	return (tab);
}
