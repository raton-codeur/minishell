/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char_and_string.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 15:38:33 by qhauuy            #+#    #+#             */
/*   Updated: 2023/12/05 16:16:21 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_char(int c, int *error)
{
	int	result;

	result = write(1, &c, 1);
	if (result < 0)
	{
		*error = 1;
		return (0);
	}
	return (result);
}

int	ft_print_string(char *s, int *error)
{
	int	result;

	if (s == NULL)
		result = write(1, "(null)", 6);
	else
		result = write(1, s, ft_strlen(s));
	if (result < 0)
	{
		*error = 1;
		return (0);
	}
	return (result);
}
