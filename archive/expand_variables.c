/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:56:37 by qhauuy            #+#    #+#             */
/*   Updated: 2024/06/05 18:09:16 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

// void print_keys(void *p)
// {
// 	printf("key : <%s>\n", (char *)p);
// }




// int expand_is_possible(int in_double_quote, int in_simple_quote)
// {
// 	return (in_double_quote
// 		|| (!in_double_quote && !in_simple_quote));
// }

// int	expand_keys(t_list **keys)
// {
// 	t_list	*key;
// 	char	*content;
// 	char	*key_value;
// 	int		in_double_quote;
// 	int		in_simple_quote;

// 	key = *keys;
// 	in_double_quote = 0;
// 	in_simple_quote = 0;
// 	while (key)
// 	{
// 		content = key->content;
// 		if (expand_is_possible(in_double_quote, in_simple_quote) && content[0] == '$' && ft_isword_start(content[1])) // variable correct
// 		{
// 			key_value = getenv(content + 1);
// 			if (key_value) // existe
// 			{
// 				free(content);
// 				key->content = ft_strdup(key_value);
// 				if (key->content == NULL)
// 					return (1);
// 			}
// 			else // existe pas
// 			{
// 				free(content);
// 				key->content = NULL;
// 			}
// 		}
// 		else if (*content == '$' && *(content + 1)) // variable incorrect
// 		{
// 			key_value = ft_strdup(content + 2);
// 			if (key_value == NULL)
// 				return (1);
// 			free(content);
// 			key->content = key_value;
// 		}
// 		// else // pas de variable
// 		key = key->next;
// 	}
// 	return (0);
// }

// int	sub_keys(t_list **result, char *content, int start, int end)
// {
// 	char	*node_content;
// 	t_list	*node;

// 	node_content = ft_substr(content, start, end - start);
// 	if (node_content == NULL)
// 		return (list_clear(result, free), 1);
// 	node = list_new(node_content);
// 	if (node == NULL)
// 		return (free(node_content), list_clear(result, free), 1);
// 	list_add_back(result, node);
// 	return (0);
// }

// t_list	*split_in_keys(char *content)
// {
// 	t_list	*result;
// 	int		start;
// 	int		end;

// 	result = NULL;
// 	start = 0;
// 	end = 0;
// 	while (content[end])
// 	{
// 		end++;
// 		if (content[end - 1] == '$')
// 		{
// 			while (ft_isword_content(content[end]))
// 				end++;
// 			if (sub_keys(&result, content, start, end) == 1)
// 				return (NULL);
// 		}
// 		else
// 		{
// 			if (sub_keys(&result, content, start, end) == 1)
// 				return (NULL);
// 		}
// 		start = end;
// 	}
// 	return (result);
// }



// int	expand_variables_token(t_list **node)
// {
// 	t_token	*token;
// 	char	*content;
// 	t_list	*keys;

// 	token = (*node)->content;
// 	content = token->content;
// 	keys = split_in_keys(content);
// 	if (keys == NULL)
// 		return (1);
// 	// if (expand_keys(&keys))
// 	// 	return (list_clear(&keys, free), 1);
// 	list_print(keys, print_keys);
// 	token->content = ft_strjoin_list(keys);
// 	if (token->content == NULL)
// 		return (list_clear(&keys, free), 1);
// 	return (0);
// }

// int	expand_variables(t_list **tokens)
// {
// 	t_list	*node;
// 	t_token	*token;
// 	int		type;

// 	node = *tokens;
// 	while (node)
// 	{
// 		token = node->content;
// 		type = token->type;
// 		if ((type == TOKEN_FILE || type == TOKEN_COMMAND)
// 			&& expand_variables_token(&node))
// 			return (1);
// 		node = node->next;
// 	}
// 	return (0);
// }
