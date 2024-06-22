/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 18:44:08 by qhauuy            #+#    #+#             */
/*   Updated: 2024/04/15 17:41:17 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;
	int	position_c;

	position_c = -1;
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			position_c = i;
		i++;
	}
	if ((char)c == '\0')
		return ((char *)(s + i));
	if (position_c == -1)
		return (NULL);
	else
		return ((char *)(s + position_c));
}
