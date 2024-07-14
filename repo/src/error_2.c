/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 15:58:43 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/14 15:07:50 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_pathname_error(char *cmd, t_data *data)
{
	char	*message;

	message = ft_strjoin(cmd, ": command not found");
	if (!message)
		error_exit(MALLOC, data);
	ft_putendl_fd(message, 2);
	free(message);
	free_all(data);
	exit(127);
}

void	heredoc_error(t_data *data)
{
	perror("minishell");
	free_all(data);
	exit(1);
}
