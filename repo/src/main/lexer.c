/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteste <jteste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:09:53 by qhauuy            #+#    #+#             */
/*   Updated: 2024/06/26 12:46:23 by jteste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

// int	main(void)
// {
// 	t_data	data;

// 	init_data(&data);
// 	while (1)
// 	{
// 		data.input = readline("minishell> ");
// 		if (data.input == NULL)
// 			return (error_exit(READLINE), 1);
// 		else
// 		{
// 			if (ft_strcmp(data.input, "exit") == 0)
// 				return (mmm_free_all(), 0);
// 			if (data.input[0] != '\0' && !ft_strisspace(data.input))
// 				add_history(data.input);
// 			get_tokens(&data);
// 			lexing(&data);
// 			list_print(data.tokens, print_token);
// 			reset_input(&data);
// 		}
// 	}
// 	return (mmm_free_all(), 0);
// }
