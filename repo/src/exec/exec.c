/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 19:22:08 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/04 19:46:35 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static pid_t	child_right(t_tree *tree, t_data *data, int pipe_[2])
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		error_exit(FORK, data);
	if (pid == 0)
	{
		data->in = pipe_[0];
		close(pipe_[1]);
		exec_cmd(tree, data, 0);
	}
	return (pid);
}

static pid_t	child_left(t_tree *tree, t_data *data, int pipe_[2])
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		error_exit(FORK, data);
	if (pid == 0)
	{
		data->out = pipe_[1];
		close(pipe_[0]);
		if (get_type(tree) == T_PIPE)
			exec_pipe(tree, data, 0);
		else
			exec_cmd(tree, data, 0);
	}
	return (pid);
}

void	exec_pipe(t_tree *tree, t_data *data, int in_parent)
{
	pid_t	pid[2];
	int		pipe_[2];
	int		status;

	if (pipe(pipe_))
		error_exit(PIPE, data);
	pid[0] = child_right(tree->right, data, pipe_);
	pid[1] = child_left(tree->left, data, pipe_);
	close(pipe_[0]);
	close(pipe_[1]);
	waitpid(pid[0], &status, 0);
	waitpid(pid[1], NULL, 0);
	if (WIFEXITED(status))
	{
		if (in_parent)
			data->exit_status = WEXITSTATUS(status);
		else
			return (free_all(data), exit(WEXITSTATUS(status)));
	}
}

void	exec(t_data *data)
{
	if (data->ast == NULL)
		return ;
	if (get_type(data->ast) == T_PIPE)
		exec_pipe(data->ast, data, 1);
	else
		exec_cmd_as_parent(data->ast, data);
}
