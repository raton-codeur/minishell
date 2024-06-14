/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 11:37:44 by jteste            #+#    #+#             */
/*   Updated: 2024/05/24 13:33:07 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	new_length(char *str)
{
	int		i;
	int		count;
	char	quote;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			count += 2;
			quote = str[i];
			i++;
			while (str[i] != quote)
				i++;
			i++;
		}
		else
			i++;
	}
	return (ft_strlen(str) - count);
}

static char	*copy_new_content(char *str, char *out)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			quote = str[i];
			i++;
			while (str[i] != quote)
				out[j++] = str[i++];
			i++;
		}
		else
		{
			out[j++] = str[i];
			i++;
		}
	}
	out[j] = '\0';
	return (out);
}

static char	*remove_quotes_content(char *str)
{
	char	*out;
	int		length;

	length = new_length(str);
	out = ft_calloc(length + 1, sizeof(char));
	if (out == NULL)
		return (NULL);
	out = copy_new_content(str, out);
	return (out);
}

int	remove_quotes(t_list **tokens)
{
	t_list	*current;
	t_token	*token;
	char	*new_content;

	current = *tokens;
	while (current)
	{
		token = current->content;
		new_content = remove_quotes_content(token->content);
		if (new_content == NULL)
			return (1);
		free(token->content);
		token->content = new_content;
		current = current->next;
	}
	return (0);
}
