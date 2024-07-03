/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:32:51 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/03 17:23:26 by qhauuy           ###   ########.fr       */
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

void	exec_cmd(t_tree *tree, t_data *data, int in_parent)
{
	pid_t	pid;
	int		status;

	/* si on est dans le parent, il faut sauvegarder stdin et stdout avec dup */
	set_redirections(&tree, data);
	dup2(data->in, 0);
	dup2(data->out, 1);
	if (exec_builtin(tree, data, in_parent))
		return ;
	else if (in_parent)
	{
		pid = fork();
		if (pid == -1)
			error_exit(FORK, data);
		else if (pid == 0)
			run_cmd(tree, data);
		else
		{
			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
				data->exit_status = WEXITSTATUS(status);
		}
		/* il faut remettre stdin et stdout */
	}
	else
		run_cmd(tree, data);
}
