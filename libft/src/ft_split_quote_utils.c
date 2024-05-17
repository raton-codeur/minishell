/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quote_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 22:39:33 by qhauuy            #+#    #+#             */
/*   Updated: 2024/04/26 22:47:54 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_size_inside_quotes(const char *s)
{
	char	type_of_quote;
	int		i;

	i = 0;
	type_of_quote = s[i++];
	while (s[i] && s[i] != type_of_quote)
		i++;
	if (s[i] != type_of_quote)
		return (-1);
	return (i - 1);
}
