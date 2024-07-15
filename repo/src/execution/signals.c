/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteste <jteste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 14:05:28 by jteste            #+#    #+#             */
/*   Updated: 2024/07/15 14:19:22 by jteste           ###   ########.fr       */
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

void	sigint_handler_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_status = 130;
	}
}