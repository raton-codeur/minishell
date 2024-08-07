/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:12:57 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/13 14:12:52 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

// int	main(void)
// {
// 	t_data	data;

// 	init_data(&data);
// 	while (1)
// 	{
// 		data.input = readline("minishell> ");
// 		if (data.input == NULL)
// 			return (error_exit(READLINE, &data), 1);
// 		else
// 		{
// 			if (ft_strcmp(data.input, "exit") == 0)
// 				return (free_all(&data), 0);
// 			if (data.input[0] != '\0' && !ft_strisspace(data.input))
// 				add_history(data.input);
// 			get_tokens(&data);
// 			lexing(&data);
// 			init_ast(&data);
// 			build_tree(&data.ast, &data);
// 			tree_print(data.ast);
// 			reset_input(&data);
// 		}
// 	}
// 	return (free_all(&data), 0);
// }
