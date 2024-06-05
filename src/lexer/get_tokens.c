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
	int		i;
	t_list	*node;

	i = 0;
	while (data->input[i])
	{
		data->s = ft_calloc(2, sizeof(char));
		if (data->s == NULL)
			error_exit(MALLOC, data);
		data->s[0] = data->input[i];
		data->t = ft_calloc(1, sizeof(t_token));
		if (data->t == NULL)
			error_exit(MALLOC, data);
		data->t->content = data->s;
		data->t->type = get_type(data->input[i]);
		node = list_new(data->t);
		if (data->s == NULL)
			error_exit(MALLOC, data);
		list_add_back(&data->tokens, node);
		i++;
	}
}
