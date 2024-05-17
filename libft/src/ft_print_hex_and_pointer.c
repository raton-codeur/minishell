/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex_and_pointer.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:58:02 by qhauuy            #+#    #+#             */
/*   Updated: 2023/12/05 17:19:30 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_unsigned_hex(unsigned long n, char format, int *error)
{
	int		result;
	char	*s;

	s = ft_itoa_unsigned_hex(n, format);
	if (s == NULL)
	{
		*error = 1;
		return (0);
	}
	result = ft_print_string(s, error);
	free(s);
	return (result);
}

char	*ft_itoa_unsigned_hex(unsigned long n, char format)
{
	char	*result;
	int		length_n;
	int		i;

	length_n = ft_length_unsigned_hex(n);
	result = ft_calloc(length_n + 1, sizeof(char));
	if (result == NULL)
		return (NULL);
	i = length_n - 1;
	while (i >= 0)
	{
		result[i--] = ft_unit_decimal_to_hex(n % 16, format);
		n /= 16;
	}
	return (result);
}

int	ft_length_unsigned_hex(unsigned long n)
{
	int	i;

	if (n == 0)
		return (1);
	i = 0;
	while (n != 0)
	{
		n /= 16;
		i++;
	}
	return (i);
}

char	ft_unit_decimal_to_hex(int n, char format)
{
	if (n >= 0 && n <= 9)
		return (n + '0');
	else if (format == 'X')
		return (n - 10 + 'A');
	else
		return (n - 10 + 'a');
}

int	ft_print_pointer(void *p, int *error)
{
	char	*s;
	char	*s_join;
	int		result;

	s = ft_itoa_unsigned_hex((unsigned long)p, 'x');
	s_join = ft_strjoin("0x", s);
	if (s == NULL || s_join == NULL)
	{
		free(s);
		*error = 1;
		return (0);
	}
	free(s);
	result = ft_print_string(s_join, error);
	free(s_join);
	return (result);
}
