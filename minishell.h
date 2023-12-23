/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npremont <npremont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 10:40:07 by npremont          #+#    #+#             */
/*   Updated: 2023/12/23 18:20:39 by npremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>

/* STRUCT */

typedef struct s_globvar
{
	char	*name;
	char	*value;
}	t_globvar;

/* ENV INIT */

char		**ft_envinit(char **envp);

/* BUILT INS */

void		ft_pwd(void);
void		ft_env(char **env_list);
void		ft_cd(char **args, char ***en);
void		ft_export(char **args, char ***en);
void		ft_unset(char **args, char ***en);
void		ft_echo(char **args);

/* CD UTILS */

char		*ft_gethome(char **en);
char		*ft_get_oldpwd(char **en);
char		*ft_tilde(char **env, char *pwd);
char		**ft_updatevar(char **en, char *name, char *value);
char		*ft_getvarline(char **en, char *varname);

/* BUILTINS UTILS */

void		ft_tabdup(char **dst, char **src);
char		**ft_addvar(char **en, char *var);
int			ft_isnot_nl(char *str);

/* EPXORT UTILS */

void		ft_display_exp(char **en);
int			ft_gettype(char *arg);
char		**ft_updatevar_exp(char **en, char *arg);

/* UNSET UTILS */

int			ft_getline_pos(char **en, char *arg);
char		**ft_rmvar(char **en, int pos);

#endif
