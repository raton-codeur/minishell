/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:09:53 by qhauuy            #+#    #+#             */
/*   Updated: 2024/06/23 19:26:51 by qhauuy           ###   ########.fr       */
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
// 			return (error_exit(READLINE, &data), 1);
// 		else
// 		{
// 			if (ft_strcmp(data.input, "exit") == 0)
// 				return (free_all(&data), 0);
// 			if (data.input[0] != '\0' && !ft_strisspace(data.input))
// 				add_history(data.input);
// 			get_tokens(&data);
// 			lexing(&data);
// 			list_print(data.tokens, print_token);
// 			reset_input(&data);
// 		}
// 	}
// 	return (free_all(&data), 0);
// }
