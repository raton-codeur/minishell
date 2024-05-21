/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:05:48 by qhauuy            #+#    #+#             */
/*   Updated: 2024/05/21 16:36:17 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/* a supprimer
pour list_print */
void	print_token(void *p)
{
	t_token	*token;

	token = p;
	printf("content : <%s>\n", token->content);
	if (token->type == T_WORD)
		printf("type : WORD\n");
	if (token->type == T_PIPE)
		printf("type : PIPE\n");
	if (token->type == T_SIMPLE_CHEVRON_LEFT)
		printf("type : SIMPLE_CHEVRON_LEFT\n");
	if (token->type == T_SIMPLE_CHEVRON_RIGHT)
		printf("type : SIMPLE_CHEVRON_RIGHT\n");
}

int	get_char_type(char c)
{
	int	result;

	if (ft_isalpha(c) || ft_isdigit(c))
		result = C_WORD;
	else if (ft_isspace(c))
		result = C_WHITE_SPACE;
	else if (c == '|')
		result = C_PIPE;
	else if (c == '>')
		result = C_SIMPLE_CHEVRON_RIGHT;
	else if (c == '<')
		result = C_SIMPLE_CHEVRON_LEFT;
	else if (c == '\0')
		result = C_END_OF_STRING;
	else
		result = C_ERROR;
	return (result);
}

/* a tout moment : C_ERROR -> erreur et pas le mettre dans TOKEN_TYPE*/
t_list	*get_tokens(char *input)
{
	int		current_token_type;
	int		i_start;
	int		i_end;
	t_list	*result;
	t_token	*token;
	t_list	*node;

	i_start = 0;
	i_end = 0;
	result = NULL;
	while (input[i_end] && get_char_type(input[i_end]) == C_WHITE_SPACE)
		i_end++;
	current_token_type = get_char_type(input[i_end]);
	if (current_token_type == C_END_OF_STRING)
		return (result);
	while (input[i_end])
	{
		while (get_char_type(input[i_end]) == current_token_type || get_char_type(input[i_end]) == C_WHITE_SPACE)
			i_end++;
		token = malloc(sizeof(t_token));
		node = list_new(token);
		token->content = ft_substr(input, i_start, i_end - i_start);
		token->type = current_token_type;
		list_add_back(&result, node);
		current_token_type = get_char_type(input[i_end]);
		i_start = i_end;
	}
	return (result);
}


