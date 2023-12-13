/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npremont <npremont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 10:40:07 by npremont          #+#    #+#             */
/*   Updated: 2023/12/13 16:27:27 by npremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

/* GLOBAL VAR */

t_list	*env_list;

/* STRUCT */

typedef struct s_globvar
{
	char	*name;
	char	*value;
}	t_globvar;

/* ENV INIT */

int			ft_envinit(char **envp);
char		*ft_getvarname(char *line);
char		*ft_getvarvalue(char *line);
t_globvar	*ft_newvar(char *line);

/* BUILT INS */

void		ft_pwd(void);
void		ft_env(void);
void		ft_export(char *arg);

/* BUILTINS UTILS */

int			ft_setenv(char **envp, char *name, char *value);

#endif
