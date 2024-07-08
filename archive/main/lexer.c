/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:09:53 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/08 22:56:02 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

// int	main(int argc, char **argv, char **envp)
// {
// 	t_data	data;

// 	init_data(&data, argc, argv, envp);
// 	while (1)
// 	{
// 		get_input(&data);
// 		if (ft_strcmp(data.input, "exit") == 0)
// 			return (free_all(&data), 0);
// 		if (data.input[0] != '\0' && !ft_strisspace(data.input))
// 			add_history(data.input);
// 		get_tokens(&data);
// 		lexing(&data);
// 		list_print(data.tokens, print_token);
// 		reset_input(&data);
// 	}
// 	return (free_all(&data), 0);
// }
