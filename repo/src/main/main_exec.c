/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:12:57 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/07 18:12:02 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	init_data(&data, argc, argv, envp);
	while (1)
	{
		get_input(&data);
		if (data.input[0] != '\0' && !ft_strisspace(data.input))
			add_history(data.input);
		get_tokens(&data);
		lexing(&data);
		init_ast(&data);
		build_tree(&data.ast, &data);
		get_heredocs(&data.ast, &data);
		exec(&data);

		printf("---------- env ----------\n");
		list_print(data.env, print_kv);

		reset_input(&data);
	}
	return (free_all(&data), 0);
}
