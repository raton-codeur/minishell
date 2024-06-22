/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:22:55 by qhauuy            #+#    #+#             */
/*   Updated: 2024/05/06 18:47:04 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static double	ft_atof_2(char *s)
{
	double	result;
	int		decimal_count;

	result = 0;
	if (*s == '.' || *s == ',')
	{
		s++;
		decimal_count = 0;
		while (*s >= '0' && *s <= '9')
		{
			result = result * 10 + *s - '0';
			s++;
			decimal_count++;
		}
		while (decimal_count > 0)
		{
			result /= 10;
			decimal_count--;
		}
	}
	return (result);
}

double	ft_atof(char *s)
{
	int		sign;
	double	result;

	while (*s == ' ' || ((*s >= '\t') && (*s <= '\r')))
		s++;
	sign = 1;
	if (*s == '+' || *s == '-')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	result = 0;
	while (*s >= '0' && *s <= '9')
	{
		result = result * 10 + *s - '0';
		s++;
	}
	return (sign * (result + ft_atof_2(s)));
}
