/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:06:04 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/16 14:04:17 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

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
		run_cmd(tree, data);
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
			execute_pipe(tree, data);
		else
			run_cmd(tree, data);
	}
	return (pid);
}

void	execute_pipe(t_tree *tree, t_data *data)
{
	pid_t	pid[2];
	int		pipe_[2];
	int		status;

	if (pipe(pipe_))
		error_exit(PIPE, data);
	pid[0] = child_right(tree->right, data, pipe_);
	pid[1] = child_left(tree->left, data, pipe_);
	close_2(pipe_);
	waitpid(pid[1], NULL, 0);
	waitpid(pid[0], &status, 0);
	if (WIFEXITED(status))
		return (free_all(data), exit(WEXITSTATUS(status)));
	// if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	// 	return (free_all(data), exit(130));
}
