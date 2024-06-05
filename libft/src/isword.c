/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isword.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:09:00 by qhauuy            #+#    #+#             */
/*   Updated: 2024/06/05 18:09:19 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isword_start(int c)
{
	return (ft_isalpha(c) || c == '_');
}

int	ft_isword_content(int c)
{
	return (ft_isalnum(c) || c == '_');
}

int	ft_strisword(char *s)
{
	if (!ft_isword_start(*s))
		return (0);
	s++;
	while (*s)
	{
		if (!ft_isword_content(*s))
			return (0);
		s++;
	}
	return (1);
}
