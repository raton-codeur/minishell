/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_once.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 18:46:46 by qhauuy            #+#    #+#             */
/*   Updated: 2024/06/26 17:16:00 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_doubletabfree(int i, char **dest)
{
	while (i > 0)
	{
		i--;
		mm_free(dest[i]);
	}
	mm_free(dest);
	return (NULL);
}

static	char	**ft_filltab(char const *s, char c, char **dest)
{
	int	start;
	int	end;
	int	i;

	start = 0;
	end = 0;
	i = 0;
	while (s[start] != '\0' && i < 2)
	{
		while (s[start] != '\0' && s[start] == c)
			start++;
		end = start;
		while (s[end] != '\0' && s[end] != c)
			end++;
		if (i < 1)
			dest[i] = ft_substr(s, start, end - start);
		else
			dest[i] = ft_substr(s, start, ft_strlen(s) - start);
		if (dest[i] == NULL)
			return (ft_doubletabfree(i, dest));
		i++;
		start = end;
	}
	return (dest);
}

char	**ft_split_once(char const *s, char c)
{
	char	**dest;

	if (!s)
		return (NULL);
	dest = mm_calloc(3, sizeof(char *));
	if (dest == NULL)
		return (NULL);
	dest[2] = NULL;
	dest = ft_filltab(s, c, dest);
	return (dest);
}
