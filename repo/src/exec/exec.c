/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 19:22:08 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/01 18:20:34 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	exec_child(t_tree *tree, t_data *data)
{
	set_redirections(&tree, data);
	analyse_cmd(tree, data);
	dup2(data->in, 0);
	dup2(data->out, 1);
	if (execve(data->cmd->pathname, data->cmd->argv, NULL) == -1)
		return (free_all(data), exit(127));
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
		exec_child(tree, data);
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
		{
			exec_pipe(tree, data);
			free_all(data);
			exit(0);
		}
		else
			exec_child(tree, data);
	}
	return (pid);
}

void	exec_pipe(t_tree *tree, t_data *data)
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
		data->exit_status = WEXITSTATUS(status);
}

void	exec(t_tree *tree, t_data *data)
{
	pid_t	pid;
	int		status;

	if (data->ast == NULL)
		return ;
	if (get_type(tree) == T_PIPE)
		exec_pipe(tree, data);
	else
	{
		if (ft_strcmp(get_content(tree), "exit") == 0)
			return (ft_printf("exit\n"), exit_(tree, data));
		pid = fork();
		if (pid == 0)
			exec_child(tree, data);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			data->exit_status = WEXITSTATUS(status);
	}
}
