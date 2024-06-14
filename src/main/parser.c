/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:12:57 by qhauuy            #+#    #+#             */
/*   Updated: 2024/06/14 19:51:52 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	main(void)
{
	t_data	data;

	ft_bzero(&data, sizeof(t_data));
	while (1)
	{
		reset_error(&data);
		data.input = readline("minishell> ");
		if (data.input == NULL)
			ft_putendl_fd("readline error", 2);
		else
		{
			if (ft_strcmp(data.input, "exit") == 0)
				return (free_all(&data), 0);
			if (data.input[0] != '\0' && !ft_strisspace(data.input))
				add_history(data.input);

			get_tokens(&data);
			if (lexing(&data))
				ft_putendl_fd("lexing error", 2);

			init_ast(&data);
			build_tree(&data.ast, &data);
			if (data.error.code)
				ft_putendl_fd(data.error.message, 2);
			else
				tree_print(data.ast);

			free(data.input);
			list_clear(&data.tokens, free_token);
			tree_clear(&data.ast);
		}
	}
	return (free_all(&data), 0);
}
