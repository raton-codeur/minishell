/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 18:43:19 by qhauuy            #+#    #+#             */
/*   Updated: 2024/06/04 16:15:50 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	length_dst;
	size_t	j;

	if (dst == NULL || src == NULL)
		return (0);
	if (dstsize == 0)
		return (ft_strlen(src));
	i = 0;
	while (dst[i])
	{
		if (i == dstsize - 1)
			return (dstsize + ft_strlen(src));
		i++;
	}
	length_dst = i;
	j = 0;
	while (src[j] && length_dst + j < dstsize - 1)
		dst[i++] = src[j++];
	dst[length_dst + j] = '\0';
	while (src[j])
		j++;
	return (length_dst + j);
}
