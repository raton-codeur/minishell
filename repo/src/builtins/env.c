/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteste <jteste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:41:50 by jteste            #+#    #+#             */
/*   Updated: 2024/06/25 16:59:05 by jteste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	copy_env(t_data *data, const char **envp)
{
	int		i;
	char	*line;
	char 	**split_line;
	t_envp	*new_content;
	t_list	*new_node;

	i = 0;
	if (envp == NULL || envp[0] == NULL || envp[0][0] == '\0')
		return (0);
	while (envp[i])
	{
		new_content = mmm_malloc(sizeof(t_envp));
		line = ft_strdup(envp[i]);
		if (line == NULL)
			return (printf("ici\n"),0);
		split_line = ft_split_once(line, '=');
		if (split_line == NULL)
			return (printf("ici 2\n"),0);
		new_content->key = ft_strdup(split_line[0]);
		if (new_content->key == NULL)
			return (printf("ici 3\n"),0);
		new_content->value = ft_strdup(split_line[1]);
		if (new_content->value == NULL)
			return (printf("ici 4\n"),0);
		new_node = list_new(new_content);
		if (new_node == NULL)
			return (printf("ici 5\n"),0);
		list_add_back(&data->envp, new_node);
		mmm_free(line);
		deep_free((void **)split_line, 2);
		i++;
	}
	return (1);
}

	