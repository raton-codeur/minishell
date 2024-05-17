/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 18:46:58 by qhauuy            #+#    #+#             */
/*   Updated: 2024/04/15 17:41:18 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_length(int n)
{
	int	result;

	if (n == 0)
		return (1);
	result = 0;
	if (n < 0)
	{
		result++;
		n = -n;
	}
	while (n > 0)
	{
		n /= 10;
		result++;
	}
	return (result);
}

char	*ft_itoa(int n)
{
	char	*result;
	int		i;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	result = ft_calloc(ft_length(n) + 1, sizeof(char));
	if (result == NULL)
		return (NULL);
	i = ft_length(n) - 1;
	if (n < 0)
	{
		result[0] = '-';
		n = -n;
	}
	while (i >= 0 && !(i == 0 && result[0] == '-'))
	{
		result[i--] = n % 10 + '0';
		n /= 10;
	}
	return (result);
}
