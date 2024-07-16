/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:09:24 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/16 16:15:52 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	execute(t_data *data)
{
	pid_t	pid;
	int		status;

	get_heredocs(&data->ast, data);
	signal(SIGINT, sigint_handler_parent);
	if (data->ast == NULL)
		return ;
	if (run_builtin_in_parent(data->ast, data))
		return ;
	signal(SIGINT, sigint_handler_child);
	signal(SIGQUIT, sigquit_handler);
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
	reset_signal();
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
}
