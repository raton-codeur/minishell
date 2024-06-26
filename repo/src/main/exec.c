/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteste <jteste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:12:57 by qhauuy            #+#    #+#             */
/*   Updated: 2024/06/26 12:50:11 by jteste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argc;
	(void)argv;
	init_data(&data);
	while (1)
	{
		data.input = readline("minishell> ");
		if (data.input == NULL)
			return (error_exit(READLINE), 1);
		else
		{
			if (copy_env(&data, envp) == 1)
				return (error_exit(ENV), 1);
			if (ft_strcmp(data.input, "env") == 0)
				print_envp_env(&data.envp);
			if (ft_strcmp(data.input, "export") == 0)
				print_envp_export(&data.envp);
			if (ft_strcmp(data.input, "exit") == 0)
				return (mmm_free_all(), rl_clear_history(), 0);
			if (data.input[0] != '\0' && !ft_strisspace(data.input))
				add_history(data.input);
			get_tokens(&data);
			lexing(&data);
			init_ast(&data);
			build_tree(&data.ast, &data);
			// tree_print(data.ast);
			get_heredocs(&data.ast, &data);
			exec(data.ast, &data);
			reset_input(&data);
		}
	}
	return (mmm_free_all(), rl_clear_history(), 0);
}
