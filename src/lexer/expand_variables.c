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


// char	*replace_keys(char *content, t_list *keys_position)
// {
// 	char	*result;
// 	int		i;
// 	int		j;
// 	int		k;
// 	int		*position;

// 	result = ft_calloc(1, sizeof(char));


// 	free(content);
// 	list_clear(&keys_position, free);
// 	return (result);
// }



t_list	*get_keys(t_token *token)
{
	char	*content;
	t_list	*result;
	t_list	*node;

	content = token->content;
	result = NULL;
	while (*content)
	{
		if (*content == '$' && *(content + 1) && !ft_isspace(*(content + 1)))
		{
			if (ft_isalpha(*(content + 1) || *(content + 1) == '_'))
			{
				node = list_new(content + 1);
				if (node == NULL)
				{
					list_clear(&result, NULL);
					return (NULL);
				}
				list_add_back(&result, node);
			}
		}
		content++;
	}
	return (result);
}

void print_keys(void *p)
{
	char *content;

	content = p;
	printf("key found : <%s>\n", content);
}


int	expand_variables_token(t_list **node)
{
	t_token	*token;
	t_list	*keys;

	token = (*node)->content;
	keys = get_keys(token);
	if (keys == NULL)
		return (1);
	list_print(keys, print_keys);
	// token->content = replace_keys(token->content, keys);
	// if (token->content == NULL)
	// 	return (1);
	return (0);
}

int	expand_variables(t_list **tokens)
{
	t_list	*node;
	t_token	*token;
	int		type;

	node = *tokens;
	while (node)
	{
		token = node->content;
		type = token->type;
		if ((type == TOKEN_FILE || type == TOKEN_COMMAND)
			&& expand_variables_token(&node))
			return (1);
		node = node->next;
	}
	return (0);
}
