/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 15:58:43 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/14 17:00:56 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_pathname_error(char *cmd, t_data *data)
{
	char	*message;

	message = ft_strjoin(cmd, ": command not found\n");
	if (!message)
		error_exit(MALLOC, data);
	ft_putstr_fd(message, 2);
	free(message);
	free_all(data);
	exit(127);
}

void	heredoc_error(int pipe_[2], t_data *data)
{
	ft_putchar_fd('\n', 1);
	perror("minishell: get_next_line");
	close_2(pipe_);
	free_all(data);
	exit(1);
}
