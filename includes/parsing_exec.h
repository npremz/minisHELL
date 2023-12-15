/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_exec.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 22:23:38 by lethomas          #+#    #+#             */
/*   Updated: 2023/12/15 01:04:27 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_EXEC_H
# define PARSING_EXEC_H

# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# include <string.h>

# include "../libft/includes/libft.h"

typedef enum e_token_type
{
	word,
	assignation,
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
	assignation_cmd,
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
	t_bool	do_follow_right_parenthesis;
	t_bool	is_prev_token_a_cmd_op;
	int		parenthesis_counter;
}	t_error_flag;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	t_bool			have_wildcard;
	t_bool			have_env_var;
}	t_token;

typedef struct s_cmd
{
	t_cmd_type		type;
	char			*name;
	char			**arg;
	t_token_type	type_in;
	char			**in;
	t_token_type	type_out;
	char			**out;
	t_bool			have_wildcard;
	t_btree			*root;
}	t_cmd;

typedef struct s_quote_info
{
	t_parity	parity[2];
	int			count[2];
	int			*cursor_pos;
}	t_quote_info;

int				ft_exec_cmd_line(char *command_line);

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

int				ft_token_parenthesis(t_list *token_list);

int				ft_create_cmd_list(t_list *token_list, t_list **cmd_list);
int				ft_set_cmd(t_list *token_list, int cmd_nb_token, t_cmd *cmd);
int				ft_set_cmd_redirection(t_list **token_list, t_cmd *cmd,
					t_list **list_cmd_in, t_list **list_cmd_out);
int				ft_set_cmd_in_out_arg(t_cmd *cmd, t_list *cmd_in,
					t_list *cmd_out, t_list *cmd_option);
int				ft_create_cmd_tree(t_list *cmd_list, t_btree **cmd_tree);

int				ft_exec_cmd_tree(t_btree *cmd_tree);
int				ft_launch_exec(t_btree *cmd_tree, t_cmd_type operator_out,
					int **fd_pipe_in, int *pid_child_tab);
int				ft_exec(t_cmd *cmd, char **error_arg);
int				ft_exit_child(t_cmd *cmd, int *fd_pipe_tab[2], int status,
					char *error_arg);

void			ft_free_token(void *token);
void			ft_free_token_list(t_list **token_list);
void			ft_free_cmd_list(t_list *cmd_list);
void			ft_free_cmd_tree(t_btree *cmd_tree);

#endif
