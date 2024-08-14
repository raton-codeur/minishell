/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:09:24 by qhauuy            #+#    #+#             */
/*   Updated: 2024/08/13 15:32:46 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	simple_command(t_data *data)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		error_exit(FORK, data);
	if (pid == 0)
		run_cmd(data->ast, data);
	waitpid(pid, &status, 0);
	g_exit_status = status;
}

void	execute(t_data *data)
{
	get_heredocs(&data->ast, data);
	if (data->ast == NULL || run_builtin_in_parent(data->ast, data))
		return ;
	g_exit_status = 0;
	set_child_signals();
	if (get_type(data->ast) == T_PIPE)
		execute_pipe(data->ast, data);
	else
		simple_command(data);
	set_parent_signals();
	if (WIFSIGNALED(g_exit_status) && WTERMSIG(g_exit_status) == SIGINT)
		printf("\n");
	if (WIFSIGNALED(g_exit_status) && WTERMSIG(g_exit_status) == SIGQUIT)
		printf("Quit\n");
	if ((WIFSIGNALED(g_exit_status) && WTERMSIG(g_exit_status) == SIGINT)
		|| (WIFSIGNALED(g_exit_status) && WTERMSIG(g_exit_status) == SIGQUIT))
		g_exit_status = 128 + WTERMSIG(g_exit_status);
	else if (WIFSIGNALED(g_exit_status))
		g_exit_status = 0;
	else if (WIFEXITED(g_exit_status))
		g_exit_status = WEXITSTATUS(g_exit_status);
}
