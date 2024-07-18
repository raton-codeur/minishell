/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 14:05:28 by jteste            #+#    #+#             */
/*   Updated: 2024/07/18 23:21:06 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	sigint_parent(int sig)
{
	(void)sig;
	g_exit_status = 130;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	sigint_child(int sig)
{
	(void)sig;
	g_exit_status = 130;
}

void	sigquit_child(int sig)
{
	(void)sig;
	g_exit_status = 131;
}
