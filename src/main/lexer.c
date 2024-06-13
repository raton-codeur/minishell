/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:09:53 by qhauuy            #+#    #+#             */
/*   Updated: 2024/06/13 15:16:36 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

// int	main(void)
// {
// 	t_data	data;

// 	ft_bzero(&data, sizeof(t_data));
// 	while (1)
// 	{
// 		data.input = readline("minishell> ");
// 		if (data.input == NULL)
// 			ft_putendl_fd("readline error", 2);
// 		else
// 		{
// 			if (ft_strcmp(data.input, "exit") == 0)
// 				return (free_all(&data), 0);
// 			if (data.input[0] != '\0' && !ft_strisspace(data.input))
// 				add_history(data.input);
// 			get_tokens(&data);
// 			free(data.input);
// 			if (lexing(&data))
// 				ft_putendl_fd("lexing error", 2);
// 			list_print(data.tokens, print_token);
// 			list_clear(&data.tokens, free_token);
// 		}
// 	}
// 	return (free_all(&data), 0);
// }
