/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:41:50 by jteste            #+#    #+#             */
/*   Updated: 2024/06/26 17:38:02 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static t_envp	*copy_env_line(char *env_line)
{
	t_envp	*new_content;
	char	**split_line;

	new_content = mm_calloc(1, sizeof(t_envp));
	if (new_content == NULL)
		return (NULL);
	split_line = ft_split_once(env_line, '=');
	if (split_line == NULL)
		return (NULL);
	new_content->key = ft_strdup(split_line[0]);
	if (new_content->key == NULL)
		return (NULL);
	new_content->value = ft_strdup(split_line[1]);
	if (new_content->value == NULL)
		return (NULL);
	deep_free((void **)split_line, 2);
	return (new_content);

}
int	copy_env(t_data *data, char **envp)
{
	int		i;
	t_envp	*new_content;
	t_list	*new_node;

	i = 0;
	if (envp == NULL || envp[0] == NULL || envp[0][0] == '\0')
		return (1);
	while (envp[i])
	{
		new_content = copy_env_line(envp[i]);
		if (new_content == NULL)
			return (error_exit(MALLOC, data),1);
		new_node = list_new(new_content);
		if (new_node == NULL)
			return (error_exit(MALLOC, data),1);
		list_add_back(&data->envp, new_node);
		i++;
	}
	return (0);
}

