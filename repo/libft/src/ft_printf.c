/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 17:17:38 by qhauuy            #+#    #+#             */
/*   Updated: 2024/04/17 14:31:44 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *s, ...)
{
	va_list	ap;
	int		result;
	int		error;

	va_start(ap, s);
	result = 0;
	error = 0;
	while (*s)
	{
		if (*s == '%')
		{
			s++;
			result += ft_print_param(*s, ap, &error);
		}
		else
			result += ft_print_char(*s, &error);
		s++;
	}
	va_end(ap);
	if (error)
		return (-1);
	return (result);
}

int	ft_print_param(char format, va_list ap, int *error)
{
	int	result;

	result = 0;
	if (format == 'c')
		result += ft_print_char(va_arg(ap, int), error);
	else if (format == 's')
		result += ft_print_string(va_arg(ap, char *), error);
	else if (format == 'p')
		result += ft_print_pointer(va_arg(ap, void *), error);
	else if (format == 'd' || format == 'i')
		result += ft_print_int(va_arg(ap, int), error);
	else if (format == 'u')
		result += ft_print_unsigned(va_arg(ap, unsigned int), error);
	else if (format == 'x' || format == 'X')
		result += ft_print_unsigned_hex(\
			va_arg(ap, unsigned int), format, error);
	else if (format == '%')
		result += ft_print_char('%', error);
	else
	{
		result += ft_print_char('%', error);
		result += ft_print_char(format, error);
	}
	return (result);
}
