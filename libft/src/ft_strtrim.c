/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 18:46:21 by qhauuy            #+#    #+#             */
/*   Updated: 2024/04/15 17:41:18 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_char_in_set(char c, const char *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*result;
	size_t	i_start;
	size_t	i_end;
	size_t	i;

	if (s1 == NULL)
		return (NULL);
	if (set == NULL)
		return (ft_strdup(s1));
	i_start = 0;
	while (s1[i_start] && ft_char_in_set(s1[i_start], set))
		i_start++;
	i_end = ft_strlen(s1);
	while (i_start < i_end && ft_char_in_set(s1[i_end - 1], set))
		i_end--;
	result = malloc(sizeof(char) * (i_end - i_start + 1));
	if (result == NULL)
		return (NULL);
	i = 0;
	while (i_start < i_end)
		result[i++] = s1[i_start++];
	result[i] = '\0';
	return (result);
}
