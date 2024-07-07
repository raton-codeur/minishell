/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:09:24 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/07 15:01:15 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	exec_cmd_in_new_child(t_tree *tree, t_data *data)
{
	pid_t	pid;
	int		status;

	if (tree == NULL)
		return ;
	pid = fork();
	if (pid == -1)
		error_exit(FORK, data);
	if (pid == 0)
	{
		if (get_type(tree) == T_PIPE)
			exec_pipe(tree, data);
		else
			run_cmd(tree, data);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		data->exit_status = WEXITSTATUS(status);
}

static int	exec_builtin_in_parent(t_tree *tree, t_data *data)
{
	(void)data;
	while (is_broket(tree))
		tree = tree->right;
	if (tree == NULL)
		return (0);
	if (ft_strcmp(get_content(tree), "cd") == 0)
	{
		printf("on fait un cd\n");
		return (1);
	}
	else if (ft_strcmp(get_content(tree), "exit") == 0)
	{
		exit_(tree, data, 1);
		return (1);
	}
	else if (ft_strcmp(get_content(tree), "export") == 0)
	{
		printf("on fait un export dans le parent\n");
		return (1);
	}
	else if (ft_strcmp(get_content(tree), "unset") == 0)
	{
		printf("on fait un unset dans le parent\n");
		return (1);
	}
	else
		return (0);
}

void	exec(t_data *data)
{
	if (data->ast == NULL)
		return ;
	if (!exec_builtin_in_parent(data->ast, data))
		exec_cmd_in_new_child(data->ast, data);
}
