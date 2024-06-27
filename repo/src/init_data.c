/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 18:04:29 by qhauuy            #+#    #+#             */
/*   Updated: 2024/06/27 12:52:39 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

static char	**add_slash(char **path)
{
	char	**result;
	int		i;
	int		n;

	n = get_length(path);
	result = ft_calloc(n + 1, sizeof(char *));
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
	if (get_env("PATH", data->envp) == NULL)
	{
		data->path = NULL;
		return ;
	}
	data->path = ft_split(get_env("PATH", data->envp), ":");
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
	data->exit_status = 0;
	get_path(data);
}
