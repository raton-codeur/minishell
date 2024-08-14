/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 18:46:46 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/07 15:45:03 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_length(const char *s, const char *delimiter)
{
	size_t	result;
	int		condition;

	result = 0;
	condition = ft_strchr(delimiter, *s) == 0;
	while (*s && ((ft_strchr(delimiter, *s) == 0) == condition))
	{
		result++;
		s++;
	}
	return (result);
}

static size_t	ft_count_words(const char *s, const char *delimiter)
{
	size_t	result;

	result = 0;
	if (ft_strchr(delimiter, *s))
		s += ft_length(s, delimiter);
	while (*s)
	{
		s += ft_length(s, delimiter);
		s += ft_length(s, delimiter);
		result++;
	}
	return (result);
}

char	**ft_split(const char *s, const char *delimiter)
{
	char	**result;
	size_t	i;

	if (s == NULL)
		return (NULL);
	result = ft_calloc(ft_count_words(s, delimiter) + 1, sizeof(char *));
	if (result == NULL)
		return (NULL);
	if (ft_strchr(delimiter, *s))
		s += ft_length(s, delimiter);
	i = 0;
	while (*s)
	{
		result[i] = ft_calloc(ft_length(s, delimiter) + 1, sizeof(char));
		if (result[i] == NULL)
			return (deep_free((void **)result, i), NULL);
		ft_strlcpy(result[i++], s, ft_length(s, delimiter) + 1);
		s += ft_length(s, delimiter);
		s += ft_length(s, delimiter);
	}
	result[i] = NULL;
	return (result);
}
