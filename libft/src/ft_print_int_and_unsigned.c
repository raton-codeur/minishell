/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int_and_unsigned.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 15:39:23 by qhauuy            #+#    #+#             */
/*   Updated: 2023/12/05 16:55:45 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_int(int n, int *error)
{
	char	*s;
	int		result;

	s = ft_itoa(n);
	if (s == NULL)
	{
		*error = 1;
		return (0);
	}
	result = ft_print_string(s, error);
	free(s);
	return (result);
}

int	ft_print_unsigned(unsigned int n, int *error)
{
	char	*s;
	int		result;

	s = ft_itoa_unsigned(n);
	if (s == NULL)
	{
		*error = 1;
		return (0);
	}
	result = ft_print_string(s, error);
	free(s);
	return (result);
}

char	*ft_itoa_unsigned(unsigned int n)
{
	char	*result;
	int		length_n;
	int		i;

	length_n = ft_length_unsigned(n);
	result = ft_calloc(length_n + 1, sizeof(char));
	if (result == NULL)
		return (NULL);
	i = length_n - 1;
	while (i >= 0)
	{
		result[i--] = n % 10 + '0';
		n /= 10;
	}
	return (result);
}

int	ft_length_unsigned(unsigned long n)
{
	int	i;

	if (n == 0)
		return (1);
	i = 0;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}
