/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteste <jteste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:05:48 by qhauuy            #+#    #+#             */
/*   Updated: 2024/05/21 17:00:8 by jteste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	get_type(char c)
{
	if (c == '|')
		return (T_PIPE);
	else if (c == '>')
		return (T_BROKET_RIGHT);
	else if (c == '<')
		return (T_BROKET_LEFT);
	else if (c == '\'')
		return (T_SIMPLE_QUOTE);
	else if (c == '"')
		return (T_DOUBLE_QUOTE);
	else if (c == '$')
		return (T_DOLLAR);
	else if (ft_isspace(c))
		return (T_WHITE_SPACE);
	else if (ft_isprint(c))
		return (T_CHARACTER);
	else
		return (T_ERROR);
}

void	get_tokens(t_data *data)
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
		new.token->type = get_type(new.content[0]);
		new.node = list_new(new.token);
		if (new.node == NULL)
		{
			free(new.content);
			free(new.token);
			error_exit(MALLOC, data);
		}
		list_add_back(&data->tokens, new.node);
		i++;
	}
}
