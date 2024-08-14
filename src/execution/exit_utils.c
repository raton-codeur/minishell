/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 18:21:30 by qhauuy            #+#    #+#             */
/*   Updated: 2024/08/13 18:55:39 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	is_nbr(const char *s)
{
	while (ft_isspace(*s))
		s++;
	if (*s == '+' || *s == '-')
		s++;
	while (*s >= '0' && *s <= '9')
		s++;
	while (ft_isspace(*s))
		s++;
	return (*s == '\0');
}

static void	trim_trailing_white_space(char **s, int i)
{
	while ((*s)[i] && !ft_isspace((*s)[i]))
		i++;
	(*s)[i] = '\0';
}

int	is_long_long(char *n, t_data *data)
{
	int	i;

	n = ft_strdup(n);
	if (n == NULL)
		error_exit(MALLOC, data);
	if (!is_nbr(n))
		return (free(n), 0);
	i = 0;
	while (ft_isspace(n[i]))
		i++;
	trim_trailing_white_space(&n, i);
	if (n[i] == '+')
	{
		if ((ft_strlen(skip_zeros(n + i + 1)) > 19)
			|| (ft_strcmp(skip_zeros(n + i + 1), "9223372036854775807") > 0))
			return (free(n), 0);
	}
	else if (n[i] == '-')
	{
		if ((ft_strlen(skip_zeros(n + i + 1))) > 19
			|| ft_strcmp(skip_zeros(n + i + 1), "9223372036854775808") > 0)
			return (free(n), 0);
	}
	else if (ft_strlen(skip_zeros(n + i)) > 19
		|| (ft_strcmp(skip_zeros(n + i), "9223372036854775807") > 0))
		return (free(n), 0);
	return (free(n), 1);
}

long long	ft_atoll(const char *s)
{
	long long	result;
	int			sign;

	while (*s == ' ' || (*s >= '\t' && *s <= '\r'))
		s++;
	sign = 1;
	if (*s == '-' || *s == '+')
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
	return (sign * result);
}
