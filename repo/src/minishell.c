/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteste <jteste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:12:57 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/11 17:50:36 by jteste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

unsigned char	g_exit_status;

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	init_data(&data, argc, argv, envp);
	signal(SIGINT, sigint_handler_parent);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		get_input(&data);
		signal(SIGINT, sigint_handler_parent);
		signal(SIGQUIT, SIG_IGN);
		parsing(&data);
		// list_print(data.tokens, print_token);
		build_AST(&data);
		// tree_print(data.ast);
		execute(&data);
		reset_input(&data);
	}
	return (free_all(&data), 0);
}
