/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 15:37:00 by qhauuy            #+#    #+#             */
/*   Updated: 2024/06/04 15:37:24 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_length_result(t_list *list)
{
	int		lenght;
	t_list	*current;

	lenght = 0;
	current = list;
	while (current)
	{
		lenght += ft_strlen(current->content);
		current = current->next;
	}
	return (lenght);
}

char	*ft_strjoin_list(t_list *list)
{
	int		length;
	char	*result;

	length = get_length_result(list);
	result = ft_calloc(length + 1, sizeof(char));
	if (result == NULL)
		return (NULL);
	while (list)
	{
		ft_strlcat(result, list->content, length + 1);
		list = list->next;
	}
	return (result);
}
