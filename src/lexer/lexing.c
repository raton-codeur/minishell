/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:20:43 by qhauuy            #+#    #+#             */
/*   Updated: 2024/06/05 18:30:29 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"











void	remove_token_type(t_data *data, int type)
{
	t_list	*tmp;
	char	quote;

	set_token(data, data->tokens);
	quote = 0;
	while (data->l)
	{
		if (data->t->type == type)
		{
			tmp = data->l;
			data->l = data->l->next;
			list_remove_node(&data->tokens, tmp, free_node);
		}
		else
			data->l = data->l->next;
		set_token(data, data->l);
	}
}


int	analyse_quotes(t_data *data)
{
	char	quote;

	quote = 0;
	set_token(data, data->tokens);
	while (data->l)
	{
		if (quote == 0)
		{
			if (data->s[0] == '\'' || data->s[0] == '"')
				quote = data->s[0];
		}
		else
		{
			if (data->s[0] == quote)
				quote = 0;
			else if (!(data->s[0] == '$' && quote == '"'))
				data->t->type = T_CHARACTER;
		}
		set_token(data, data->l->next);
	}
	return (quote != 0);
}


void	find_dollar(t_data *data)
{
	t_token	*next;

	set_token(data, data->tokens);
	while (data->l)
	{
		if (data->l->next)
		{
			next = data->l->next->content;
			if (data->t->type == T_DOLLAR)
			{
				if (next->type == T_CHARACTER
					&& ft_isword_content(next->content[0]))
					printf("trouve\n");
				else
					data->t->type = T_CHARACTER;
			}
		}
		else if (data->t->type == T_DOLLAR)
			data->t->type = T_CHARACTER;
		set_token(data, data->l->next);
	}
}

int	lexing(t_data *data)
{
	if (analyse_quotes(data))
		return (1);
	broket_to_double_broket(data);
	find_dollar(data);
	// remove_token_type(data, T_DOUBLE_QUOTE);
	return (0);
}
