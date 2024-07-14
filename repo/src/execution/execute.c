/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:09:24 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/14 17:21:24 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	run_in_new_child(t_tree *tree, t_data *data)
{
	pid_t	pid;
	int		status;

	if (tree == NULL)
		return ;
	pid = fork();
	if (pid == -1)
		error_exit(FORK, data);
	if (pid == 0)
	{
		if (get_type(tree) == T_PIPE)
			exec_pipe(tree, data);
		else
			run_cmd(tree, data);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
}

static int	run_builtin_in_parent(t_tree *tree, t_data *data)
{
	while (tree && get_broket(tree->content))
		tree = tree->right;
	if (tree == NULL)
		return (1);
	if (ft_strcmp(get_content(tree), "cd") == 0)
		return (cd_(tree, data, 1), 1);
	else if (ft_strcmp(get_content(tree), "export") == 0)
		return (export_(tree, data, 1));
	else if (ft_strcmp(get_content(tree), "unset") == 0)
		return (unset_(tree, data, 1));
	else if (ft_strcmp(get_content(tree), "exit") == 0)
		return (exit_(tree, data, 1));
	else
		return (0);
}

int	end_builtin(int in_parent, int exit_status, t_data *data)
{
	g_exit_status = exit_status;
	if (!in_parent)
	{
		free_all(data);
		exit(exit_status);
	}
	return (1);
}

void	execute(t_data *data)
{
	if (data->ast == NULL)
		return ;
	get_heredocs(&data->ast, data);
	if (!run_builtin_in_parent(data->ast, data))
		run_in_new_child(data->ast, data);
}
