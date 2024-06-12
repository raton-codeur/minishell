/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:09:53 by qhauuy            #+#    #+#             */
/*   Updated: 2024/06/12 17:47:07 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	print_type(int type)
{
	if (type == T_PIPE)
		printf("type : PIPE\n");
	else if (type == T_BROKET_LEFT)
		printf("type : BROKET_LEFT\n");
	else if (type == T_BROKET_RIGHT)
		printf("type : BROKET_RIGHT\n");
	else if (type == T_SIMPLE_QUOTE)
		printf("type : SIMPLE_QUOTE\n");
	else if (type == T_DOUBLE_QUOTE)
		printf("type : DOUBLE_QUOTE\n");
	else if (type == T_DOLLAR)
		printf("type : DOLLAR\n");
	else if (type == T_WHITE_SPACE)
		printf("type : WHITE_SPACE\n");
	else if (type == T_CHARACTER)
		printf("type : CHARACTER\n");
	else if (type == T_ERROR)
		printf("type : ERROR\n");
	else if (type == T_VARIABLE)
		printf("type : VARIABLE\n");
	else if (type == T_WORD)
		printf("type : WORD\n");
	else if (type == T_COMMAND)
		printf("type : COMMAND\n");
	else if (type == T_FILE)
		printf("type : FILE\n");
	else if (type == T_DELIMITER)
		printf("type : DELIMITER\n");
	else if (type == T_DOUBLE_BROKET_LEFT)
		printf("type : DOUBLE_BROKET_LEFT\n");
	else if (type == T_DOUBLE_BROKET_RIGHT)
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
			get_tokens(&data);
			free(data.input);
			if (lexing(&data))
				ft_putendl_fd("lexing error", 2);
			list_print(data.tokens, print_token);
			list_clear(&data.tokens, free_token);
		}
	}
	return (free_all(&data), 0);
}
