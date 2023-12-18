/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npremont <npremont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 10:40:07 by npremont          #+#    #+#             */
/*   Updated: 2023/12/18 18:40:21 by npremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

/* STRUCT */

typedef struct s_globvar
{
	char	*name;
	char	*value;
}	t_globvar;

/* ENV INIT */

char		**ft_envinit(char **envp, char **env);

/* BUILT INS */

void		ft_pwd(void);
void		ft_env(char **env_list);

/* BUILTINS UTILS */

#endif
