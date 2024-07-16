/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 14:05:28 by jteste            #+#    #+#             */
/*   Updated: 2024/07/16 16:12:26 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

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
		printf("\n");
		g_exit_status = 130;
	}
}

void	set_sigint_handler_heredoc(void)
{
	struct sigaction	sa;

	sa.sa_handler = sigint_handler_child;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		error_exit(SIGACTION, NULL);
}

void	sigquit_handler(int sig)
{
	if (sig == SIGQUIT)
	{
		g_exit_status = 131;
		printf("Quit\n");
		signal(SIGQUIT, SIG_IGN);
	}
}

void	reset_signal(void)
{
	signal(SIGINT, sigint_handler_parent);
	signal(SIGQUIT, SIG_IGN);
}
