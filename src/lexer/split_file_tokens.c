/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_file_tokens.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:40:24 by qhauuy            #+#    #+#             */
/*   Updated: 2024/05/23 15:36:52 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	has_white_space(char *token_content)
{
	while (*token_content)
	{
		if (ft_isspace(*token_content))
			return (1);
		token_content++;
	}
	return (0);
}

static char	**split_file_token(char *token_content)
{
	char	**result;
	int		i;

	result = ft_calloc(2, sizeof(char *));
	if (result == NULL)
		return (NULL);
	i = 0;
	while (token_content[i] && !ft_isspace(token_content[i]))
		i++;
	result[0] = ft_substr(token_content, 0, i);
	result[1] = ft_substr(token_content, i, ft_strlen(token_content) - i);
	if (result[0] == NULL || result[1] == NULL)
		return (deep_free(result, 2), NULL);
	return (result);
}

static int	insert_new_tokens(t_list *current, char **tokens_contents)
{
	t_token	*token;
	t_list	*new_node;
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (new_token == NULL)
		return (deep_free(tokens_contents, 2), 1);
	new_node = list_new(&new_token);
	if (new_node == NULL)
		return (deep_free(tokens_contents, 2), free(new_token), 1);
	token = current->content;
	token->content = tokens_contents[0];
	new_node->content = new_token;
	new_token->content = tokens_contents[1];
	free(tokens_contents);
	new_token->type = TOKEN_COMMAND;
	new_node->next = current->next;
	current->next = new_node;
	new_node->previous = current;
	if (new_node->next)
		new_node->next->previous = new_node;
	return (0);
}

int	split_file_tokens(t_list **tokens)
{
	t_list	*current;
	t_token	*token;
	char	**new_tokens;

	current = *tokens;
	while (current)
	{
		token = current->content;
		if (token->type == TOKEN_FILE && has_white_space(token->content))
		{
			new_tokens = split_file_token(token->content);
			if (new_tokens == NULL)
				return (1);
			if (insert_new_tokens(current, new_tokens))
				return (1);
		}
		current = current->next;
	}
	return (0);
}
