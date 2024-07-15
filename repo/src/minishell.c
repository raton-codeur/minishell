/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:12:57 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/15 17:52:33 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

unsigned char	g_exit_status;

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	init_data(&data, argc, argv, envp);
	while (1)
	{
		get_input(&data);
		parse(&data);
		// list_print(data.tokens, print_token);
		build_ast(&data);
		// tree_print(data.ast);
		execute(&data);
		reset_input(&data);
	}
	return (free_all(&data), 0);
}

// int main()
// {
// 	struct sigaction sa;

//     sa.sa_handler = sigint_handler_heredoc;
// 	// sigemptyset(&sa.sa_mask);
// 	// sa.sa_flags = 0;
// 	sigaction(SIGINT, &sa, NULL);

// 	int fd = 0;
// 	char *s = get_next_line(fd);
// 	printf("%s\n", s);
// }
