/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_signals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 23:15:47 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/19 00:19:04 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_child_signals(void)
{
	signal(SIGINT, sigint_child);
	signal(SIGQUIT, sigquit_child);
}

void	set_parent_signals(void)
{
	signal(SIGINT, sigint_parent);
	signal(SIGQUIT, SIG_IGN);
}

void	set_heredoc_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = sigint_child;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGINT, &sa, NULL) == -1)
		error_exit(SIGACTION, NULL);
	signal(SIGQUIT, SIG_IGN);
}
