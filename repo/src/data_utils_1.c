/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_utils_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 18:04:29 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/15 17:52:44 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_env(t_data *data, char **envp)
{
	int	i;

	i = 0;
	if (envp == NULL)
		return (minimum_env(data));
	while (envp[i])
		insert_in_env(envp[i++], data);
	minimum_env(data);
}

void	init_data(t_data *data, int argc, char **argv, char **envp)
{
	(void)argc,
	(void)argv;
	ft_bzero(data, sizeof(t_data));
	data->out = 1;
	init_env(data, envp);
	get_path(data);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigint_handler_parent);
}

static char	**add_slash(char **path)
{
	char	**result;
	int		i;
	int		n;

	n = array_size(path);
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
	if (get_value(in_env("PATH", data)) == NULL)
	{
		data->path = NULL;
		return ;
	}
	data->path = ft_split(get_value(in_env("PATH", data)), ":");
	if (data->path == NULL)
		error_exit(MALLOC, data);
	data->path = add_slash(data->path);
	if (data->path == NULL)
		error_exit(MALLOC, data);
}
