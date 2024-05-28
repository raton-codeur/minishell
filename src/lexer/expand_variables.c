/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:56:37 by qhauuy            #+#    #+#             */
/*   Updated: 2024/05/24 13:47:57 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	insert_value(t_list **node, int i)
{
	t_token	*token;
	char	*key;
	char	*new_content;
	int		len;

	token = (*node)->content;
	key = ft_substr(token->content, i, get_key_length(token, i));
	if (key == NULL)
		return (1);
	len = ft_strlen(token->content) + ft_strlen(getenv(key)) - ft_strlen(key);
	new_content = ft_calloc(len, sizeof(char));
	if (new_content == NULL)
		return (free(key), 1);
	ft_strncpy(new_content, token->content, i - 1);
	ft_strcpy(new_content + i - 1, getenv(key));
	ft_strcpy(new_content + i - 1 + ft_strlen(getenv(key)),
		token->content + i + ft_strlen(key));
	free(token->content);
	token->content = new_content;
	free(key);
	return (0);
}

static int	remove_bad_variable(t_list **node, int i)
{
	t_token	*token;
	char	*new_content;

	token = (*node)->content;
	new_content = ft_calloc(ft_strlen(token->content) - 1, sizeof(char));
	if (new_content == NULL)
		return (1);
	ft_strncpy(new_content, token->content, i - 1);
	ft_strcpy(new_content + i - 1, token->content + i + 1);
	free(token->content);
	token->content = new_content;
	return (0);
}

static int	expand_variables_token(t_list **node, int *in_double_quote)
{
	int		i;

	i = find_dollar((*node)->content, in_double_quote);
	while (i != -1)
	{
		if (is_good_variable((*node)->content, i))
		{
			if (insert_value(node, i))
				return (1);
		}
		else if (remove_bad_variable(node, i))
			return (1);
		i = find_dollar((*node)->content, in_double_quote);
	}
	return (0);
}

int	expand_variables(t_list **tokens)
{
	t_list	*node;
	t_token	*token;
	int		type;
	int		in_double_quote;

	node = *tokens;
	while (node)
	{
		in_double_quote = 0;
		token = node->content;
		type = token->type;
		if ((type == TOKEN_FILE || type == TOKEN_COMMAND)
			&& expand_variables_token(&node, &in_double_quote))
			return (1);
		node = node->next;
	}
	return (0);
}
