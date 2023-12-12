/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 22:23:38 by lethomas          #+#    #+#             */
/*   Updated: 2023/12/12 01:30:14 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../libft/includes/libft.h"

typedef enum e_token_type
{
	word,
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

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	t_bool			have_wildcard;
	t_bool			have_env_var;
}	t_token;

typedef struct s_cmd
{
	char			*name;
	char			**arg;
	t_token_type	type_in;
	char			*in;
	t_token_type	type_out;
	char			*out;
	t_bool			have_wildcard;
}	t_cmd;

typedef struct s_quote_info
{
	t_parity	parity[2];
	int			count[2];
	int			*cursor_pos;
}	t_quote_info;

int				ft_create_token_list(char *command_line, t_list **token_list);

int				ft_set_token_value(char *command_line, int token_begin_pos,
					int cursor_pos, t_token *token);
int				ft_add_new_token(t_list **token_list, t_token *token);
t_token_type	ft_get_token_type(char *str);
t_bool			ft_is_an_op(char *command_line);

void			ft_free_token(void *token);
void			ft_free_token_list(t_list **token_list);

int				ft_single_quote(char **command_line, int *cursor_pos,
					t_token *token, int *token_begin_pos);
int				ft_double_quote(char **command_line, int *cursor_pos,
					t_token *token, int *token_begin_pos);

int				ft_check_cmd_validity(t_list *token_list);
int				ft_check_redirection_validity(t_list *token_list);

int				ft_parenthesis_redirection(t_list *token_list);

#endif
