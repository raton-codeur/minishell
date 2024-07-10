/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:05:19 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/10 10:47:48 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	select_builtin(t_tree *tree, t_data *data)
{
	if (ft_strcmp(get_content(tree), "echo") == 0)
		echo_(tree, data);
	if (ft_strcmp(get_content(tree), "cd") == 0)
		cd_(tree, data, 0);
	if (ft_strcmp(get_content(tree), "pwd") == 0)
		pwd_(data);
	if (ft_strcmp(get_content(tree), "export") == 0)
		export_(tree, data, 0);
	if (ft_strcmp(get_content(tree), "unset") == 0)
		unset_(tree, data, 0);
	if (ft_strcmp(get_content(tree), "env") == 0)
		env_(data);
	if (ft_strcmp(get_content(tree), "exit") == 0)
		exit_(tree, data, 0);
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

void	run_cmd(t_tree *tree, t_data *data)
{
	char	**envp;

	set_redirections(&tree, data);
	if (tree == NULL)
		return (free_all(data), exit(0));
	dup2(data->in, 0);
	dup2(data->out, 1);
	select_builtin(tree, data);
	if (has_slash(get_content(tree)))
		analyse_file((tree), data);
	else
		prepare_exec_absolute(tree, data);
	envp = get_envp(data);
	if (execve(data->cmd->pathname, data->cmd->argv, envp) == -1)
	{
		deep_free((void **)envp, array_size(envp));
		return (free_all(data), exit(127));
	}
}
