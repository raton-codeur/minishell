/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteste <jteste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 14:05:28 by jteste            #+#    #+#             */
/*   Updated: 2024/07/16 10:14:00 by jteste           ###   ########.fr       */
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
		g_exit_status = 130;
		printf("\n");
	}
}

void	set_sigint_handler_heredoc(void)
{
	struct sigaction sa;
	sa.sa_handler = sigint_handler_child;
	sigaction(SIGINT, &sa, NULL);
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
