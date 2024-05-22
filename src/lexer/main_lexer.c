/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:09:53 by qhauuy            #+#    #+#             */
/*   Updated: 2024/05/22 18:07:50 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/* a supp */
void	print_type(int type)
{
	if (type == TOKEN_PIPE)
		printf("type : TOKEN_PIPE\n");
	else if (type == TOKEN_BROKET_LEFT)
		printf("type : TOKEN_BROKET_LEFT\n");
	else if (type == TOKEN_BROKET_RIGHT)
		printf("type : TOKEN_BROKET_RIGHT\n");
	else if (type == TOKEN_WHITE_SPACE)
		printf("type : TOKEN_WHITE_SPACE\n");
	else if (type == TOKEN_WORD)
		printf("type : TOKEN_WORD\n");
	else if (type == TOKEN_ERROR)
		printf("type : TOKEN_ERROR\n");
	else if (type == TOKEN_COMMAND)
		printf("type : TOKEN_COMMAND\n");
	else if (type == TOKEN_FILE)
		printf("type : TOKEN_FILE\n");
	else if (type == TOKEN_DELIMITER)
		printf("type : TOKEN_DELIMITER\n");
	else if (type == TOKEN_DOUBLE_BROKET_LEFT)
		printf("type : TOKEN_DOUBLE_BROKET_LEFT\n");
	else if (type == TOKEN_DOUBLE_BROKET_RIGHT)
		printf("type : TOKEN_DOUBLE_BROKET_RIGHT\n");
	else if (type == TOKEN_QUOTE)
		printf("type : TOKEN_QUOTE\n");
	else if (type == TOKEN_DOUBLE_QUOTE)
		printf("type : TOKEN_DOUBLE_QUOTE\n");
}

/*
a supprimer
pour list print
*/
void	print_token(void *p)
{
	t_token	*token;

	token = p;
	printf("content : <%s>\n", token->content);
	print_type(token->type);
}

int	main(void)
{
	char	*input;
	t_list	*tokens;

	tokens = NULL;
	while (1)
	{
		input = readline("minishell> ");
		if (input == NULL)
			ft_putendl_fd("error", 2);
		else
		{
			if (input[0] != '\0' && !ft_strisspace(input))
				add_history(input);
			if (get_tokens(&tokens, input) || lexing(&tokens))
				ft_putendl_fd("lexing error", 2);
			free(input);
			list_print(tokens, print_token);
			list_clear(&tokens, free_token);
		}
	}
	rl_clear_history();
	return (EXIT_SUCCESS);
}
