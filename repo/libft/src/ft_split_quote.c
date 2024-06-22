/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 13:34:01 by qhauuy            #+#    #+#             */
/*   Updated: 2024/06/04 18:44:03 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_word_size(const char *s, char c)
{
	int	i;

	if (*s == '\'' || *s == '\"')
		return (ft_size_inside_quotes(s));
	else
	{
		i = 0;
		while (s[i] && s[i] != c && s[i] != '\'' && s[i] != '\"')
			i++;
	}
	return (i);
}

static int	ft_word_full_size(const char *s, char c)
{
	if (*s == '\'' || *s == '\"')
		return (ft_word_size(s, c) + 2);
	else
		return (ft_word_size(s, c));
}

static int	ft_count_words(const char *s, char c)
{
	int	result;
	int	n;

	result = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		n = ft_word_size(s, c);
		if (n == -1)
			return (-1);
		else if (n == 0)
			s += ft_word_full_size(s, c);
		else
		{
			result++;
			s += ft_word_full_size(s, c);
		}
	}
	return (result);
}

char	*ft_get_word(const char *s, char c)
{
	char	*result;
	int		n;

	n = ft_word_size(s, c);
	result = ft_calloc(n + 1, sizeof(char));
	if (result == NULL)
		return (NULL);
	if (*s == '\'' || *s == '\"')
		s++;
	ft_strncpy(result, s, n);
	return (result);
}

char	**ft_split_quote(const char *s, char c)
{
	char	**result;
	size_t	i;

	if (s == NULL || !ft_isprint(c) || ft_count_words(s, c) == -1)
		return (NULL);
	result = ft_calloc(ft_count_words(s, c) + 1, sizeof(char *));
	if (result == NULL)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (ft_word_size(s, c) != 0)
		{
			result[i] = ft_get_word(s, c);
			if (result[i] == NULL)
				return (deep_free((void **)result, i), NULL);
			i++;
		}
		s += ft_word_full_size(s, c);
	}
	result[i] = NULL;
	return (result);
}
