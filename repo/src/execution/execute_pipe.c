/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:06:04 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/19 00:23:44 by qhauuy           ###   ########.fr       */
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
	int		status[2];

	if (pipe(pipe_))
		error_exit(PIPE, data);
	pid[0] = child_left(tree->left, data, pipe_);
	pid[1] = child_right(tree->right, data, pipe_);
	close_2(pipe_);
	waitpid(pid[0], &status[0], 0);
	waitpid(pid[1], &status[1], 0);
	free_all(data);

	if (WIFEXITED(status[1]))
		g_exit_status = WEXITSTATUS(status[1]);

	else if (WIFSIGNALED(status[1]) && WTERMSIG(status[1]) == SIGINT)
		g_exit_status = 130;
	else if (WIFSIGNALED(status[1]) && WTERMSIG(status[1]) == SIGQUIT)
		g_exit_status = 131;

	if (WIFEXITED(status[0]) && WEXITSTATUS(status[0]) == 130)
		exit(130);
	if (WIFEXITED(status[0]) && WEXITSTATUS(status[0]) == 131)
		exit(131);

	if (WIFSIGNALED(status[0]) && WTERMSIG(status[0]) == SIGINT)
		exit(130);
	if (WIFSIGNALED(status[0]) && WTERMSIG(status[0]) == SIGQUIT)
		exit(131);

	if (WIFEXITED(status[1]))
		exit(WEXITSTATUS(status[1]));
}
