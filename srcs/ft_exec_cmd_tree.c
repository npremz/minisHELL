/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmd_tree.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 17:08:28 by lethomas          #+#    #+#             */
/*   Updated: 2024/03/07 15:32:24 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_get_nb_cmd(t_btree *cmd_tree, t_btree *root, int *nb_cmd)
{
	if (cmd_tree == NULL)
		return ;
	if (cmd_tree->left == NULL && cmd_tree->right == NULL)
	{
		(*nb_cmd)++;
		((t_cmd *)cmd_tree->item)->root = root;
	}
	if (cmd_tree->left != NULL)
		ft_get_nb_cmd(cmd_tree->left, root, nb_cmd);
	if (cmd_tree->right != NULL)
		ft_get_nb_cmd(cmd_tree->right, root, nb_cmd);
}

static int	ft_or_and_cmd_condition(t_cmd_type operator_out,
	pid_t *pid_child_tab, t_bool *do_continue)
{
	int	i;

	i = 1;
	if (operator_out == and_operator_cmd
		|| operator_out == or_operator_cmd)
	{
		while (pid_child_tab[i + 1] != 0)
			i++;
		if (pid_child_tab[i] != -19)
			if (waitpid(pid_child_tab[i], pid_child_tab, 0) == -1)
				return (EXIT_FAILURE);
		pid_child_tab[i] = -19;
		pid_child_tab[0] = WEXITSTATUS(pid_child_tab[0]);
		if (operator_out == and_operator_cmd && pid_child_tab[0] != 0)
			*do_continue = false;
		if (operator_out == or_operator_cmd && pid_child_tab[0] == 0)
			*do_continue = false;
	}
	return (EXIT_SUCCESS);
}

static int	ft_init_exec(t_btree *cmd_tree, t_cmd_type operator_out, int **fd_pipe_in,
	int *pid_child_tab, t_list **env)
{
	int *fd_pipe_in_out[2];
	int	*fd_pipe_out;

	fd_pipe_out = NULL;
	if (operator_out == pipe_operator_cmd)
	{
		fd_pipe_out = (int *)malloc(2 * sizeof(int));
		if (fd_pipe_out == NULL)
			return (EXIT_FAILURE);
		if (pipe(fd_pipe_out) == -1)
			return (EXIT_FAILURE);
	}
	fd_pipe_in_out[0] = *fd_pipe_in;
	fd_pipe_in_out[1] = fd_pipe_out;
	if (ft_launch_exec((t_cmd *)cmd_tree->item, fd_pipe_in_out, pid_child_tab, env))
		return (EXIT_FAILURE);
	*fd_pipe_in = fd_pipe_in_out[0];
	return (EXIT_SUCCESS);
}

static int	ft_exec_cmd_tree_rec(t_btree *cmd_tree, t_cmd_type operator_out,
	int **fd_pipe_in, pid_t *pid_child_tab, t_list **env)
{
	t_bool		do_continue;
	t_cmd_type	new_operator_out;

	do_continue = true;
	if (((t_cmd *)cmd_tree->item)->type == classic_cmd
		|| ((t_cmd *)cmd_tree->item)->type == assignation_cmd)
	{
		if (ft_init_exec(cmd_tree, operator_out, fd_pipe_in, pid_child_tab, env))
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	new_operator_out = ((t_cmd *)cmd_tree->item)->type;
	if (ft_exec_cmd_tree_rec(cmd_tree->left, new_operator_out, fd_pipe_in,
			pid_child_tab, env))
		return (EXIT_FAILURE);
	if (ft_or_and_cmd_condition(new_operator_out, pid_child_tab, &do_continue))
		return (EXIT_FAILURE);
	if (do_continue == true)
		if (ft_exec_cmd_tree_rec(cmd_tree->right, operator_out, fd_pipe_in,
				pid_child_tab, env))
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	ft_wait_for_children(pid_t *pid_child_tab)
{
	int		i;
	int		j;
	t_bool	is_last_child;
	int		status;

	j = 1;
	while (pid_child_tab[j] != -42)
	{
		if (pid_child_tab[j] != 0 && pid_child_tab[j] != -19)
		{
			if (waitpid(pid_child_tab[j], &status, 0) == -1)
				return (EXIT_FAILURE);
			pid_child_tab[j] = -19;
			i = 0;
			is_last_child = true;
			while (pid_child_tab[j + ++i] != -42)
				if (pid_child_tab[j + i] != 0)
					is_last_child = false;
			if (is_last_child == true)
				pid_child_tab[0] = WEXITSTATUS(status);
		}
		j++;
	}
	return (EXIT_SUCCESS);
}

int	ft_exec_cmd_tree(t_btree *cmd_tree, t_list **env)
{
	t_cmd_type	operator_out;
	int			*fd_pipe_in;
	int			nb_cmd;
	pid_t		*pid_child_tab;

	operator_out = and_operator_cmd;
	fd_pipe_in = NULL;
	ft_get_nb_cmd(cmd_tree, cmd_tree, &nb_cmd);
	pid_child_tab = (pid_t *)ft_calloc(nb_cmd + 2, sizeof(pid_t));
	if (pid_child_tab == NULL)
		return (EXIT_FAILURE);
	pid_child_tab[nb_cmd + 1] = -42;
	if (ft_exec_cmd_tree_rec(cmd_tree, operator_out,
			&fd_pipe_in, pid_child_tab, env))
		return (EXIT_FAILURE);
	if (ft_wait_for_children(pid_child_tab))
		return (EXIT_FAILURE);
	ft_free_cmd_tree(cmd_tree);
	return (pid_child_tab[0]);
}
