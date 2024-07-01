/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 19:22:08 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/01 23:07:53 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	exec_pipe(t_tree *tree, t_data *data);

static char	*get_pathname(char *name, t_data *data)
{
	char	*result;
	int		i;

	result = NULL;
	i = 0;
	if (data->path == NULL)
		return (NULL);
	while (data->path[i])
	{
		result = ft_strjoin(data->path[i], name);
		if (result == NULL)
			error_exit(MALLOC, data);
		if (access(result, X_OK) == 0)
			return (result);
		free(result);
		i++;
	}
	cmd_pathname_error(name, data);
	return (NULL);
}

static int	get_argc(t_tree *tree)
{
	if (tree == NULL)
		return (0);
	return (1 + get_argc(tree->left));
}

void	prepare_argv(t_tree *tree, t_data *data)
{
	int		i;

	if (tree == NULL)
		return ;
	data->cmd = ft_calloc(1, sizeof(t_cmd));
	if (data->cmd == NULL)
		error_exit(MALLOC, data);
	data->cmd->argc = get_argc(tree);
	data->cmd->argv = ft_calloc(data->cmd->argc + 1, sizeof(char *));
	if (data->cmd->argv == NULL)
		error_exit(MALLOC, data);
	i = 0;
	while (i < data->cmd->argc)
	{
		data->cmd->argv[i++] = get_content(tree);
		tree = tree->left;
	}
	data->cmd->argv[i] = NULL;
}

void	prepare_exec_absolute(t_tree *tree, t_data *data)
{
	prepare_argv(tree, data);
	data->cmd->pathname = get_pathname(data->cmd->argv[0], data);
}

void	prepare_exec_relative(t_tree *tree, t_data *data)
{
	prepare_argv(tree, data);
	data->cmd->pathname = ft_strdup(data->cmd->argv[0]);
	if (data->cmd->pathname == NULL)
		error_exit(MALLOC, data);
}

int	has_slash(char *s)
{
	while (*s)
	{
		if (*s == '/')
			return (1);
		s++;
	}
	return (0);
}

void	analyse_file(t_tree *tree, t_data *data)
{
	struct stat	sb;
	char		*name;

	name = get_content(tree);
	if (stat(name, &sb) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		return (perror(name), free_all(data), exit(127));
	}
	if (S_ISDIR(sb.st_mode))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(name, 2);
		ft_putendl_fd(": Is a directory", 2);
		return (free_all(data), exit(126));
	}
	if (access(name, R_OK | X_OK) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		return (perror(name), free_all(data), exit(126));
	}
	else
		prepare_exec_relative(tree, data);
}

static void	exec_cmd(t_tree *tree, t_data *data, int in_parent)
{
	pid_t	pid;
	int		status;

	set_redirections(&tree, data);
	dup2(data->in, 0);
	dup2(data->out, 1);
	if (ft_strcmp(get_content(tree), "exit") == 0)
		exit_(tree, data, in_parent);
	else
	{
		pid = fork();
		if (pid == 0)
		{
			if (has_slash(get_content(tree)))
				analyse_file((tree), data);
			else
				prepare_exec_absolute(tree, data);
			if (execve(data->cmd->pathname, data->cmd->argv, NULL) == -1)
				return (free_all(data), exit(127));
		}
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			data->exit_status = WEXITSTATUS(status);
	}
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
		{
			exec_pipe(tree, data);
			free_all(data);
			exit(0);
		}
		else
			exec_cmd(tree, data, 0);
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

void	exec(t_data *data)
{
	if (data->ast == NULL)
		return ;
	if (get_type(data->ast) == T_PIPE)
		exec_pipe(data->ast, data);
	else
		exec_cmd(data->ast, data, 1);
}
