/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteste <jteste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 18:04:29 by qhauuy            #+#    #+#             */
/*   Updated: 2024/06/25 13:29:29 by jteste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**add_slash(char **path)
{
	char	**result;
	int		i;
	int		n;

	n = get_length(path);
	result = mmm_malloc((n + 1) * sizeof(char *));
	if (result == NULL)
		return (deep_free((void **)path, n), NULL);
	i = 0;
	while (i < n)
	{
		result[i] = ft_strjoin(path[i], "/");
		if (result[i] == NULL)
		{
			deep_free((void **)result, i);
			deep_free((void **)path, n);
			return (NULL);
		}
		i++;
	}
	result[i] = NULL;
	deep_free((void **)path, n);
	return (result);
}

void	get_path(t_data *data)
{
	if (getenv("PATH") == NULL)
	{
		data->path = NULL;
		return ;
	}
	data->path = ft_split(getenv("PATH"), ":");
	if (data->path == NULL)
		error_exit(MALLOC, data);
	data->path = add_slash(data->path);
	if (data->path == NULL)
		error_exit(MALLOC, data);
}

void	init_data(t_data *data)
{
	ft_bzero(data, sizeof(t_data));
	data->in = 0;
	data->out = 1;
	get_path(data);
}
