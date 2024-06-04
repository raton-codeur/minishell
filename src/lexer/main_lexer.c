/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:09:53 by qhauuy            #+#    #+#             */
/*   Updated: 2024/06/04 21:32:05 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	print_type(int type)
{
	if (type == TYPE_PIPE)
		printf("type : PIPE\n");
	else if (type == TYPE_BROKET_LEFT)
		printf("type : BROKET_LEFT\n");
	else if (type == TYPE_BROKET_RIGHT)
		printf("type : BROKET_RIGHT\n");
	else if (type == TYPE_SIMPLE_QUOTE)
		printf("type : SIMPLE_QUOTE\n");
	else if (type == TYPE_DOUBLE_QUOTE)
		printf("type : DOUBLE_QUOTE\n");
	else if (type == TYPE_WHITE_SPACE)
		printf("type : WHITE_SPACE\n");
	else if (type == TYPE_CHARACTER)
		printf("type : CHARACTER\n");
	else if (type == TYPE_ERROR)
		printf("type : ERROR\n");
	else if (type == TYPE_WORD)
		printf("type : WORD\n");
	else if (type == TYPE_COMMAND)
		printf("type : COMMAND\n");
	else if (type == TYPE_FILE)
		printf("type : FILE\n");
	else if (type == TYPE_DELIMITER)
		printf("type : DELIMITER\n");
	else if (type == TYPE_DOUBLE_BROKET_LEFT)
		printf("type : DOUBLE_BROKET_LEFT\n");
	else if (type == TYPE_DOUBLE_BROKET_RIGHT)
		printf("type : DOUBLE_BROKET_RIGHT\n");
}

void	print_token(void *p)
{
	t_token	*token;

	token = p;
	printf("content : <%s>\n", token->content);
	print_type(token->type);
}






int	main(void)
{
	t_data	data;

	ft_bzero(&data, sizeof(t_data));
	while (1)
	{
		data.input = readline("minishell> ");
		if (data.input == NULL)
			ft_putendl_fd("readline error", 2);
		else
		{
			if (ft_strcmp(data.input, "exit") == 0)
				break ;
			if (data.input[0] != '\0' && !ft_strisspace(data.input))
				add_history(data.input);
			if (get_tokens(&data))
			// if (get_tokens(&data) || lexing(&data))
				ft_putendl_fd("lexing error", 2);
			free(data.input);
			list_print(data.tokens, print_token);
			list_clear(&data.tokens, free_node);
		}
	}
	return (free_all(&data), 0);
}
