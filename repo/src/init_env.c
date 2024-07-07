/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 16:32:34 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/07 18:13:19 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_kv	*get_new_content(char *env_line)
{
	t_kv	*result;
	int		i;

	result = ft_calloc(1, sizeof(t_kv));
	if (result == NULL)
		return (NULL);
	i = 0;
	while (env_line[i] && env_line[i] != '=')
		i++;
	result->key = ft_substr(env_line, 0, i);
	result->value = ft_substr(env_line, i + 1, ft_strlen(env_line) - i - 1);
	if (result->key == NULL || result->value == NULL)
		return (NULL);
	return (result);
}

void	check_SHLVL(t_data *data)
{
	t_kv	*new_content;
	t_list	*new_node;

	if (get_from_env("SHLVL", data) == NULL)
	{
		new_content = get_new_content("SHLVL=1");
		if (new_content == NULL)
			return (error_exit(MALLOC, data));
		new_node = list_new(new_content);
		if (new_node == NULL)
			return (error_exit(MALLOC, data));
		list_add_back(&data->env, new_node);
	}
	else
	{
		new_content = get_new_content(ft_strjoin("SHLVL=", ft_itoa(ft_atoi(get_from_env("SHLVL", data)) + 1)));
		if (new_content == NULL)
			return (error_exit(MALLOC, data));
		new_node = list_new(new_content);
		if (new_node == NULL)
			return (error_exit(MALLOC, data));
		list_add_back(&data->env, new_node);
	}
}

void	init_env(t_data *data, char **envp)
{
	int		i;
	t_kv	*new_content;
	t_list	*new_node;

	if (envp == NULL || envp[0] == NULL)
		return ;
	i = 0;
	while (envp[i])
	{
		new_content = get_new_content(envp[i]);
		if (new_content == NULL)
			return (error_exit(MALLOC, data));
		new_node = list_new(new_content);
		if (new_node == NULL)
			return (error_exit(MALLOC, data));
		list_add_back(&data->env, new_node);
		i++;
	}
	check_SHLVL(data);
}
