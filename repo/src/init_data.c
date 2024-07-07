/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 18:04:29 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/06 13:23:25 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

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
	// if (get_env("PATH", data->envp) == NULL)
	// {
	// 	data->path = NULL;
	// 	return ;
	// }
	// data->path = ft_split(get_env("PATH", data->envp), ":");
	// if (data->path == NULL)
	// 	error_exit(MALLOC, data);
	data->path = add_slash(data->path);
	if (data->path == NULL)
		error_exit(MALLOC, data);
}

void	init_data(t_data *data, int argc, char **argv, char **envp)
{
	(void)argc,
	(void)argv;
	ft_bzero(data, sizeof(t_data));
	data->out = 1;
	(void)envp;
	// init_envp(data, envp);
	get_path(data);
}

void	get_input(t_data *data)
{
	char	*prompt;
	char	*save;

	prompt = ft_itoa(data->exit_status);
	if (prompt == NULL)
		error_exit(MALLOC, data);
	save = prompt;
	prompt = ft_strjoin("[", prompt);
	free(save);
	if (prompt == NULL)
		error_exit(MALLOC, data);
	save = prompt;
	prompt = ft_strjoin(prompt, "] minishell >>> ");
	free(save);
	if (prompt == NULL)
		error_exit(MALLOC, data);
	data->input = readline(prompt);
	free(prompt);
	if (data->input == NULL)
		error_exit(READLINE, data);
}
