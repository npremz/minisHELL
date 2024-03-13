/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npremont <npremont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 22:23:38 by lethomas          #+#    #+#             */
/*   Updated: 2024/03/13 11:42:26 by npremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# include <string.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>
# include <termios.h>

# include "../libft/includes/libft.h"

# define MAX_CWD_PATH_SIZE 256
# define BREAK 2
# define DEBUG_MODE 1

typedef enum e_token_type
{
	word,
	single_quote,
	double_quote,
	pipe_operator,
	or_operator,
	and_operator,
	left_parenthesis,
	right_parenthesis,
	redirection_in,
	redirection_out,
	redirection_append,
	redirection_here_doc
}	t_token_type;

typedef enum e_cmd_type
{
	classic_cmd,
	pipe_operator_cmd,
	or_operator_cmd,
	and_operator_cmd,
	left_parenthesis_cmd,
	right_parenthesis_cmd
}	t_cmd_type;

typedef struct s_error_flag
{
	t_bool	is_prev_token_a_redirection;
	int		cmd_size;
	t_bool	is_prev_token_a_left_parenthesis;
	t_bool	is_prev_token_a_heredoc;
	t_bool	do_follow_right_parenthesis;
	t_bool	is_prev_token_a_cmd_op;
	int		parenthesis_counter;
}	t_error_flag;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	t_list			*wildcard_list;
	t_list			*env_eff_list;
}	t_token;

typedef struct s_globvar
{
	char	*name;
	char	*value;
	int		is_secret;
}	t_globvar;

typedef struct s_sig
{
	int		sigint;
	int		sigquit;
	int		exit_status;
	pid_t	pid;
}	t_sig;

typedef struct s_cmd
{
	t_cmd_type		type;
	char			*name;
	t_list			*wildcard_name;
	t_list			*env_eff_name;
	char			**arg;
	t_list			*wildcard_arg;
	t_list			*env_eff_arg;
	char			**in;
	t_list			*wildcard_in;
	t_list			*env_eff_in;
	t_token_type	*type_in;
	char			**out;
	t_list			*wildcard_out;
	t_list			*env_eff_out;
	t_token_type	*type_out;
	t_btree			*root;
}	t_cmd;

typedef struct s_quote_info
{
	t_parity	parity[2];
	int			count[2];
	int			*cursor_pos;
}	t_quote_info;

t_sig	g_sig;

int				ft_exec_cmd_line(char *command_line, t_list **env);

int				ft_create_token_list(char *command_line, t_list **token_list);
int				ft_set_word_token(char **command_line, int *cursor_pos,
					t_token *token, t_error_flag *error_flag);
int				ft_set_operator_token(char **command_line, int *cursor_pos,
					t_token *token, t_error_flag *error_flag);
int				ft_set_token_value(char *command_line, int token_begin_pos,
					int cursor_pos, t_token *token);
t_bool			ft_token_is_cmd_op(t_token *token);
t_bool			ft_token_is_redirection_op(t_token *token);
t_token_type	ft_get_token_type(char *str);
int				ft_single_quote(char **command_line, int *cursor_pos,
					t_token *token, int *token_begin_pos);
int				ft_double_quote(char **command_line, int *cursor_pos,
					t_token *token, int *token_begin_pos);
int				ft_unclosed_command_line(t_token *token, char **command_line,
					t_error_flag error_flag, int cursor_pos);
int				ft_set_token_wildcard_list(t_token *token,
					t_bool is_wildcard_effective);
int				ft_set_token_env_eff_list(char *command_line, t_token *token,
					t_bool is_wildcard_effective);
int				ft_get_env_name(char *command_line, char **env_name);
t_bool			ft_str_is_an_op(char *command_line);

int				ft_token_parenthesis(t_list *token_list);

int				ft_create_cmd_list(t_list *token_list, t_list **cmd_list);
int				ft_set_cmd(t_list *token_list, int cmd_nb_token, t_cmd *cmd);
int				ft_set_cmd_redirection(t_cmd *cmd, t_list **token_list,
					t_list **list_cmd_in, t_list **list_cmd_out);
int				ft_set_cmd_in_out_arg(t_cmd *cmd, t_list *cmd_in,
					t_list *cmd_out, t_list *cmd_option);

int				ft_set_env_calls(t_cmd *cmd, t_list *en, int debug);
char			*ft_unsplit(char **tab, char *c);
void			ft_debug(t_cmd *cmd);
void			ft_add_var_len_to_res(int *i, int *len, char *var_name,
					t_list *en);
int				ft_add_var_to_res(char **res, char *var, t_list *en, int i[3]);
char			*ft_basename(char *str);

int				ft_set_wildcard_for_cmd(t_cmd *cmd);
int				ft_set_wildcard_for_cmd_name(t_cmd *cmd);
int				ft_set_wildcard_for_cmd_arg(char *arg_name, t_cmd *cmd);
void			ft_update_wildcard_bool_list_old_entry(char *wildcard_name,
					t_list **wildcard_list);
int				ft_update_wildcard_bool_list_new_entry(
					t_list *wildcard_bool_list, char *name,
					t_list **elem_prev);
int				ft_get_wildcard_value(char *wildcard_path,
					t_list **wildcard_bool_list, t_list **path_before);
int				ft_set_wildcard_name_path(char **path_after,
					char **wildcard_name, t_list *path_before,
					t_list **wildcard_bool_list);
int				ft_update_path_before(t_list **path_before,
					t_list *wildcard_value_list);
t_bool			ft_wildcard_cmp(char *with_wildcard, char *without_wildcard,
					t_list *wildcard_list);

int				ft_create_cmd_tree(t_list *cmd_list, t_btree **cmd_tree);
int				ft_exec_cmd_tree(t_btree *cmd_tree, t_list **env);
int				ft_init_exec(t_btree *cmd_tree, t_cmd_type operator_out,
					int **fd_pipe_in, int *pid_child_tab, t_list **env);
int				ft_launch_builtout(t_cmd *cmd, int **fd_pipe_in_out,
					int *pid_child_tab, t_list **env);
int				ft_set_pipe_fd(int *fd_pipe_in_out[2], int fd_in_out[2]);
int				ft_open_redirection(t_cmd *cmd, char **error_arg,
					int *fd_in_out, t_list **env);
int				ft_redirection_here_doc(int *fd_in, char *delimiter);
int				ft_exec(t_cmd *cmd, char **error_arg, t_list **env);
int				ft_exit_child(t_cmd *cmd, int *fd_pipe_tab[2], int status,
					char *error_arg);
int				ft_display_error(char *arg_error);

void			ft_free_token(void *token);
void			ft_free_token_list(t_list **token_list);
void			ft_free_cmd(void *cmd);
void			ft_free_cmd_list(t_list *cmd_list);
void			ft_free_cmd_tree(t_btree *cmd_tree);
void			ft_free_tab(char **tab);

/* SINGALS HANDLING */

void			ft_define_ctrl_c(void);
void			ft_define_ctrl_bs(void);

void			ft_new_prompt(int num);
void			ft_kill_process(int num);
void			ft_null(int num);
void			ft_mute_term(void);
void			ft_unmute_term(void);

/* EXEC BUILINS */

t_bool			ft_is_builtin(t_cmd *cmd);
int				ft_exec_builtin(t_cmd *cmd, t_list **env, int fd,
					t_bool is_child);

/* BUILTINS
**	Returns -> 1 if failed -> 0 if success
*/

int				ft_cd(char **args, t_list **en, int fd);
int				ft_export(char **args, t_list **en, int fd);
int				ft_export_var(int type, t_list **en, t_globvar *var);
int				ft_env(t_list *en, int fd);
int				ft_pwd(int fd);
int				ft_unset(char **args, t_list **en);
int				ft_echo(char **args, int fd);
int				ft_exit(t_list **en, t_bool is_child);

/* ENV init
** Clean exit if failed
*/

void			ft_envinit(t_list **en, char **envp);

/* BUILTINS UTILS */

int				ft_get_globvar(char *varline, t_globvar **var);
int				ft_print_secret(t_list *en, int fd);
char			**ft_en_to_tab(t_list *en);
int				ft_print_export(char **en, int fd);
char			*ft_get_varname(char *varline);
char			*ft_get_varvalue(char *varline);
char			*ft_get_gvar_value(char *str, t_list *en);

/* READLINE */

extern void		rl_clear_history(void);
void			rl_replace_line(const char *text, int clear_undo);

/* FREE UTILS */

void			ft_envclear(t_list **lst, void (*del)(t_globvar *));

/* ERROR HANDLING */

void			exit_error(char *str, t_list **en, t_globvar *var, int code);
void			print_error(char *str);
void			free_globvar(t_globvar *ptr);

#endif
