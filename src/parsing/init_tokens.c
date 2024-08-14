/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 22:19:36 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/16 13:50:42 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	get_type(t_iterable *new)
{
	if (new->content[0] == '|')
		new->token->type = T_PIPE;
	else if (new->content[0] == '>')
		new->token->type = T_BROKET_RIGHT;
	else if (new->content[0] == '<')
		new->token->type = T_BROKET_LEFT;
	else if (new->content[0] == '\'')
		new->token->type = T_SIMPLE_QUOTE;
	else if (new->content[0] == '"')
		new->token->type = T_DOUBLE_QUOTE;
	else if (new->content[0] == '$')
		new->token->type = T_DOLLAR;
	else if (ft_isspace(new->content[0]))
		new->token->type = T_WHITE_SPACE;
	else if (ft_isprint(new->content[0]))
		new->token->type = T_CHARACTER;
	else
		return (print_error(LEXING), 1);
	return (0);
}

void	init_tokens(t_data *data)
{
	int			i;
	t_iterable	new;

	i = 0;
	while (data->input[i])
	{
		new.content = ft_calloc(2, sizeof(char));
		if (new.content == NULL)
			error_exit(MALLOC, data);
		new.content[0] = data->input[i];
		new.token = ft_calloc(1, sizeof(t_token));
		if (new.token == NULL)
			return (free(new.content), error_exit(MALLOC, data));
		new.token->content = new.content;
		if (get_type(&new))
			return (free_token(new.token), free_input(data));
		new.node = list_new(new.token);
		if (new.node == NULL)
			return (free_token(new.token), error_exit(MALLOC, data));
		list_add_back(&data->tokens, new.node);
		i++;
	}
}
