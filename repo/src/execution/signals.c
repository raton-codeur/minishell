/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteste <jteste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:24:22 by jteste            #+#    #+#             */
/*   Updated: 2024/07/11 17:59:55 by jteste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

extern unsigned char	g_exit_status;

void	sigint_handler_parent(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_status = 130;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	sigint_handler_child(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_status = 130;
		printf("\n");
	}
}

// void	sigint_handler_heredoc(int sig)
// {
// }
