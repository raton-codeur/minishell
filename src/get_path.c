/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 23:17:51 by qhauuy            #+#    #+#             */
/*   Updated: 2024/05/21 13:08:58 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**add_slash(char **path)
{
	char	**result;
	int		i;
	int		n;

	n = get_length(path);
	result = ft_calloc(n + 1, sizeof(char *));
	if (result == NULL)
		return (deep_free(path, n), NULL);
	i = 0;
	while (i < n)
	{
		result[i] = ft_strjoin(path[i], "/");
		if (result[i] == NULL)
		{
			deep_free(result, i);
			deep_free(path, n);
			return (NULL);
		}
		i++;
	}
	result[i] = NULL;
	deep_free(path, n);
	return (result);
}

char	**get_path(void)
{
	char	**result;

	result = ft_split(getenv("PATH"), ":");
	if (result == NULL)
		return (NULL);
	result = add_slash(result);
	if (result == NULL)
		return (NULL);
	return (result);
}
