/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 11:32:54 by qhauuy            #+#    #+#             */
/*   Updated: 2024/05/24 14:07:13 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	find_dollar(t_token *token, int *in_double_quote)
{
	char	*s;
	int		i;

	s = token->content;
	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' && !(*in_double_quote))
		{
			i++;
			while (s[i] != '\'')
				i++;
			i++;
		}
		else if (s[i] == '"')
		{
			*in_double_quote = 1 - *in_double_quote;
			i++;
		}
		else
		{
			if (s[i] && s[i] == '$' && s[i + 1] && !ft_isspace(s[i + 1]))
				return (i + 1);
			i++;
		}
	}
	return (-1);
}

int	is_good_variable(t_token *token, int i)
{
	char	c;

	c = token->content[i];
	return (ft_isalpha(c) || c == '_');
}

int	get_key_length(t_token *token, int i)
{
	char	*s;
	int		j;

	s = token->content + i;
	j = 0;
	while (ft_isalnum(s[j]) || s[j] == '_')
		j++;
	return (j);
}
