/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ancien exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 19:22:08 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/05 14:28:39 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
























// static void	run_cmd(t_tree *tree, t_data *data)
// {
// 	if (has_slash(get_content(tree)))
// 		analyse_file((tree), data);
// 	else
// 		prepare_exec_absolute(tree, data);
// 	if (execve(data->cmd->pathname, data->cmd->argv, NULL) == -1)
// 		return (free_all(data), exit(127));
// }






























// int	run_builtin(t_tree *tree, t_data *data, int in_parent)
// {
// 	// if (ft_strcmp(get_content(tree), "echo") == 0)
// 	// 	return (echo_(tree, data, in_parent));
// 	// if (ft_strcmp(get_content(tree), "cd") == 0)
// 	// 	return (cd_(tree, data, in_parent), 1);
// 	// if (ft_strcmp(get_content(tree), "pwd") == 0)
// 	// 	return (pwd_(in_parent), 1);
// 	// if (ft_strcmp(get_content(tree), "export") == 0)
// 	// 	return (export_(tree, data, in_parent), 1);
// 	// if (ft_strcmp(get_content(tree), "unset") == 0)
// 	// 	return (unset_(tree, data, in_parent), 1);
// 	// if (ft_strcmp(get_content(tree), "env") == 0)
// 	// 	return (env_(&data->envp, in_parent), 1);
// 	if (ft_strcmp(get_content(tree), "exit") == 0)
// 		return (exit_(tree, data, in_parent), 1);
// 	return (0);
// }



// void	exec_cmd_parent(t_tree *tree, t_data *data)
// {
// 	pid_t	pid;
// 	int		status;

// 	pid = fork();
// 	if (pid == -1)
// 		error_exit(FORK, data);
// 	else if (pid == 0)
// 	{
// 		set_redirections(&tree, data);
// 		dup2(data->in, 0);
// 		dup2(data->out, 1);
// 		if (!run_builtin(tree, data, 1))
// 			run_cmd(tree, data);
// 	}
// 	waitpid(pid, &status, 0);
// 	if (WIFEXITED(status))
// 		data->exit_status = WEXITSTATUS(status);
// }

















// static pid_t	child_right(t_tree *tree, t_data *data, int pipe_[2])
// {
// 	pid_t	pid;

// 	pid = fork();
// 	if (pid == -1)
// 		error_exit(FORK, data);
// 	if (pid == 0)
// 	{
// 		data->in = pipe_[0];
// 		close(pipe_[1]);
// 		exec_cmd(tree, data, 0);
// 	}
// 	return (pid);
// }

// static pid_t	child_left(t_tree *tree, t_data *data, int pipe_[2])
// {
// 	pid_t	pid;

// 	pid = fork();
// 	if (pid == -1)
// 		error_exit(FORK, data);
// 	if (pid == 0)
// 	{
// 		data->out = pipe_[1];
// 		close(pipe_[0]);
// 		if (get_type(tree) == T_PIPE)
// 			exec_pipe(tree, data, 0);
// 		else
// 			exec_cmd(tree, data, 0);
// 	}
// 	return (pid);
// }

// void	exec_pipe(t_tree *tree, t_data *data, int in_parent)
// {
// 	pid_t	pid[2];
// 	int		pipe_[2];
// 	int		status;

// 	if (pipe(pipe_))
// 		error_exit(PIPE, data);
// 	pid[0] = child_right(tree->right, data, pipe_);
// 	pid[1] = child_left(tree->left, data, pipe_);
// 	close(pipe_[0]);
// 	close(pipe_[1]);
// 	waitpid(pid[0], &status, 0);
// 	waitpid(pid[1], NULL, 0);
// 	if (WIFEXITED(status))
// 	{
// 		if (in_parent)
// 			data->exit_status = WEXITSTATUS(status);
// 		else
// 			return (free_all(data), exit(WEXITSTATUS(status)));
// 	}
// }
























// void	exec(t_data *data)
// {
// 	if (data->ast == NULL)
// 		return ;
// 	if (get_type(data->ast) == T_PIPE)
// 		exec_pipe(data->ast, data, 1);
// 	else
// 		exec_cmd_as_parent(data->ast, data);
// }
