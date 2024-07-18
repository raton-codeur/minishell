/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:09:24 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/19 00:10:05 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	execute(t_data *data)
{
	pid_t	pid;
	int		status;

	get_heredocs(&data->ast, data);
	if (data->ast == NULL || run_builtin_in_parent(data->ast, data))
		return ;
	set_child_signals();
	pid = fork();
	if (pid == -1)
		error_exit(FORK, data);
	if (pid == 0)
	{
		if (get_type(data->ast) == T_PIPE)
			execute_pipe(data->ast, data);
		else
			run_cmd(data->ast, data);
	}
	waitpid(pid, &status, 0);
	set_parent_signals();
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) == 130)
			ft_putchar_fd('\n', 2);
		g_exit_status = WEXITSTATUS(status);
	}
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		ft_putchar_fd('\n', 2);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
		ft_putstr_fd("Quit\n", 2);
}
