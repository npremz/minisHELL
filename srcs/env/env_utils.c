/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npremont <npremont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:48:21 by npremont          #+#    #+#             */
/*   Updated: 2024/03/05 14:00:16 by npremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_get_varname(char *varline)
{
	size_t	i;
	char	*res;

	i = 0;
	while (varline[i] != '=' && varline[i])
		++i;
	res = malloc((i + 1) * sizeof(char));
	if (!(res))
		return (NULL);
	i = -1;
	while (varline[++i] != '=' && varline[i])
		(res)[i] = varline[i];
	res[i++] = '\0';
	return (res);
}

char	*ft_get_varvalue(char *varline)
{
	size_t	i;
	size_t	j;
	char	*res;

	i = 0;
	while (varline[i] != '=' && varline[i])
		++i;
	if (varline[i++] == '=')
	{
		j = i;
		while (varline[j] != '\0')
			j++;
		res = malloc((j - i + 1) * sizeof(char));
		if (!(res))
			return (NULL);
		j = i - 1;
		while (varline[++j] != '\0')
			res[j - i] = varline[j];
		res[j - i] = '\0';
		return (res);
	}
	res = malloc(1);
	res[0] = '\0';
	return (res);
}

size_t	get_en_len(t_list *en)
{
	size_t		len;
	t_globvar	*var;

	len = 0;
	while (en)
	{
		var = en->content;
		len += ft_strlen(var->name);
		len += ft_strlen(var->value);
		len += 2;
		en = en->next;
	}
	len += 1;
	return (len);
}

char	**ft_en_to_tab(t_list *en)
{
	char		*str;
	char		**res;
	t_globvar	*var;
	size_t		len;

	len = get_en_len(en);
	str = (char *)malloc(len * sizeof(char));
	if (!str)
		return (NULL);
	str[0] = '\0';
	while (en)
	{
		var = en->content;
		ft_strlcat(str, var->name, len);
		if (!(var->is_secret))
			ft_strlcat(str, "=", len);
		ft_strlcat(str, var->value, len);
		ft_strlcat(str, "\n", len);
		en = en->next;
	}
	res = ft_split(str, '\n');
	if (!res)
		return (NULL);
	free(str);
	return (res);
}

void	ft_print_export(char **en, int fd)
{
	size_t	i;
	size_t	j;

	i = -1;
	while (en[++i])
	{
		j = 0;
		write(fd, "declare -x ", 12);
		while (en[i][j] != '=' && en[i][j] != '\0')
			write(fd, &en[i][j++], 1);
		if (!en[i][j])
		{
			write(fd, "\n", 1);
			continue ;
		}
		write(fd, &en[i][j++], 1);
		write(fd, "\"", 2);
		while (en[i][j] != '\0')
			write(fd, &en[i][j++], 1);
		write(fd, "\"\n", 3);
	}
}
