/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:05:19 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/05 16:02:23 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	run_builtin(t_tree *tree, t_data *data)
{
	(void)tree;
	(void)data;
	printf("execution dun builtin qui va se exit tout seul \n");
	free_all(data);
	exit(0);
}

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

static int	has_builtin(t_tree *tree)
{
	if (ft_strcmp(get_content(tree), "echo") == 0)
		return (1);
	if (ft_strcmp(get_content(tree), "cd") == 0)
		return (1);
	if (ft_strcmp(get_content(tree), "pwd") == 0)
		return (1);
	if (ft_strcmp(get_content(tree), "export") == 0)
		return (1);
	if (ft_strcmp(get_content(tree), "unset") == 0)
		return (1);
	if (ft_strcmp(get_content(tree), "env") == 0)
		return (1);
	if (ft_strcmp(get_content(tree), "exit") == 0)
		return (1);
	return (0);
}

void	run_cmd(t_tree *tree, t_data *data)
{
	set_redirections(&tree, data);
	if (tree == NULL)
		return (free_all(data), exit(0));
	dup2(data->in, 0);
	dup2(data->out, 1);
	if (has_builtin(tree))
		run_builtin(tree, data);
	if (has_slash(get_content(tree)))
		analyse_file((tree), data);
	else
		prepare_exec_absolute(tree, data);
	if (execve(data->cmd->pathname, data->cmd->argv, NULL) == -1)
		return (free_all(data), exit(127));
}
