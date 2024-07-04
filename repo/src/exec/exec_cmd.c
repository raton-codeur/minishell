/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:32:51 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/04 19:45:53 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	has_slash(char *s)
{
	while (*s)
	{
		if (*s == '/')
			return (1);
		s++;
	}
	return (0);
}

static void	analyse_file(t_tree *tree, t_data *data)
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

static void	run_cmd(t_tree *tree, t_data *data)
{
	if (has_slash(get_content(tree)))
		analyse_file((tree), data);
	else
		prepare_exec_absolute(tree, data);
	if (execve(data->cmd->pathname, data->cmd->argv, NULL) == -1)
		return (free_all(data), exit(127));
}









int	run_builtin(t_tree *tree, t_data *data, int in_parent)
{
	// if (ft_strcmp(get_content(tree), "echo") == 0)
	// 	return (echo_(tree, data, in_parent));
	// if (ft_strcmp(get_content(tree), "cd") == 0)
	// 	return (cd_(tree, data, in_parent), 1);
	// if (ft_strcmp(get_content(tree), "pwd") == 0)
	// 	return (pwd_(in_parent), 1);
	// if (ft_strcmp(get_content(tree), "export") == 0)
	// 	return (export_(tree, data, in_parent), 1);
	// if (ft_strcmp(get_content(tree), "unset") == 0)
	// 	return (unset_(tree, data, in_parent), 1);
	// if (ft_strcmp(get_content(tree), "env") == 0)
	// 	return (env_(&data->envp, in_parent), 1);
	if (ft_strcmp(get_content(tree), "exit") == 0)
		return (exit_(tree, data, in_parent), 1);
	return (0);
}



void	exec_cmd_parent(t_tree *tree, t_data *data)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		error_exit(FORK, data);
	else if (pid == 0)
	{
		set_redirections(&tree, data);
		dup2(data->in, 0);
		dup2(data->out, 1);
		if (!run_builtin(tree, data, in_parent))
			run_cmd(tree, data);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		data->exit_status = WEXITSTATUS(status);
}
