/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:21:47 by qhauuy            #+#    #+#             */
/*   Updated: 2024/05/23 18:20:16 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	free_token(void *p)
{
	t_token	*token;

	token = p;
	free(token->content);
	free(token);
}

int	go_to_quote_end(char *input, t_get_tokens_utils *u)
{
	char	quote;

	quote = input[u->end];
	u->end++;
	while (input[u->end] && input[u->end] != quote)
		u->end++;
	if (input[u->end] != quote)
		return (1);
	return (0);
}

void	init_current_token(t_current_token *current_node_info, t_list *node)
{
	current_node_info->node = node;
	current_node_info->token = node->content;
	current_node_info->content = current_node_info->token->content;
	current_node_info->type = current_node_info->token->type;
}
