/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 19:22:08 by qhauuy            #+#    #+#             */
/*   Updated: 2024/06/26 17:38:44 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

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
		exec_child(tree->left, data);
	}
	return (pid);
}

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
		exec_child(tree->right, data);
	}
	return (pid);
}

static void	exec_pipe(t_tree *tree, t_data *data)
{
	pid_t	pid[2];
	int		pipe_[2];

	if (pipe(pipe_))
		error_exit(PIPE, data);
	pid[0] = child_right(tree, data, pipe_);
	pid[1] = child_left(tree, data, pipe_);
	close(pipe_[0]);
	close(pipe_[1]);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], NULL, 0);
	exit(0);
}

void	exec_child(t_tree *tree, t_data *data)
{
	if (get_type(tree) == T_PIPE)
		exec_pipe(tree, data);
	else
	{
		set_redirections(&tree, data);
		get_cmd(tree, data);
		if (data->cmd == NULL)
			return (mm_free_all(), exit(0));
		dup2(data->in, 0);
		dup2(data->out, 1);
		if (execve(data->cmd->pathname, data->cmd->argv, NULL) == -1)
		{
			perror("execve");
			free_all(data);
			exit(0);
		}
	}
}

void	exec(t_tree *tree, t_data *data)
{
	pid_t	pid;

	if (data->ast == NULL)
		return ;
	pid = fork();
	if (pid == 0)
		exec_child(tree, data);
	waitpid(pid, NULL, 0);
}
