/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:12:57 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/01 23:04:44 by qhauuy           ###   ########.fr       */
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
		// if (ft_strcmp(data.input, "env") == 0)
		// 	print_env(&data.envp);
		// if (ft_strcmp(data.input, "export") == 0)
		// 	print_export(&data.envp);
		if (data.input[0] != '\0' && !ft_strisspace(data.input))
			add_history(data.input);
		get_tokens(&data);
		lexing(&data);
		init_ast(&data);
		build_tree(&data.ast, &data);
		// tree_print(data.ast);
		get_heredocs(&data.ast, &data);
		exec(&data);
		reset_input(&data);
	}
	return (free_all(&data), 0);
}
