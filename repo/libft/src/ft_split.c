/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteste <jteste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 18:46:46 by qhauuy            #+#    #+#             */
/*   Updated: 2024/06/25 13:24:00 by jteste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_length(const char *s, const char *delimiter)
{
	unsigned int	result;
	int				condition;

	result = 0;
	condition = ft_strchr(delimiter, *s) != 0;
	while (*s && ((ft_strchr(delimiter, *s) != 0) == condition))
	{
		result++;
		s++;
	}
	return (result);
}

static unsigned int	ft_count_words(const char *s, const char *delimiter)
{
	unsigned int	result;

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

static void	ft_free_inside(char **result, unsigned int i)
{
	unsigned int	j;

	j = 0;
	while (j < i)
		mmm_free(result[j++]);
}

char	**ft_split(const char *s, const char *delimiter)
{
	char			**result;
	unsigned int	i;

	if (s == NULL)
		return (NULL);
	result = mmm_malloc((ft_count_words(s, delimiter) + 1) * sizeof(char *));
	if (result == NULL)
		return (NULL);
	if (ft_strchr(delimiter, *s))
		s += ft_length(s, delimiter);
	i = 0;
	while (*s)
	{
		result[i] = mmm_malloc((ft_length(s, delimiter) + 1) * sizeof(char));
		if (result[i] == NULL)
			return (ft_free_inside(result, i), mmm_free(result), NULL);
		ft_strlcpy(result[i++], s, ft_length(s, delimiter) + 1);
		s += ft_length(s, delimiter);
		s += ft_length(s, delimiter);
	}
	result[i] = NULL;
	return (result);
}
