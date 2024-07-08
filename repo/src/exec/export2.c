/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:32:56 by jteste            #+#    #+#             */
/*   Updated: 2024/07/08 17:36:11 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	export_error(t_list *new, t_data *data)
{
	printf("minishell: export: `%s': not a valid identifier\n", get_key(new));
	list_remove_node(&data->env, new, free_kv);
}

// t_kv	*creat_full_env_node(char *arg)
// {
// 	t_kv	*new_content;
// 	char	**split;

// 	new_content = ft_calloc(1, sizeof(t_kv));
// 	if (new_content == NULL)
// 		return (NULL);
// 	split = ft_split_once(arg, '=');
// 	if (split == NULL)
// 	{
// 		free(new_content);
// 		return (NULL);
// 	}
// 	new_content->key = split[0];
// 	new_content->value = split[1];
// 	free(split);
// 	return (new_content);
// }

// t_kv	*creat_half_env_node(char *arg)
// {
// 	t_kv	*new_content;

// 	new_content = ft_calloc(1, sizeof(t_kv));
// 	if (new_content == NULL)
// 		return (NULL);
// 	new_content->key = ft_strdup(arg);
// 	new_content->value = ft_strdup("");
// 	if (new_content->key == NULL || new_content->value == NULL)
// 	{
// 		free(new_content->key);
// 		free(new_content->value);
// 		free(new_content);
// 		return (NULL);
// 	}
// 	return (new_content);
// }

static t_kv	*copy_env_content(t_kv *content)
{
	t_kv	*new_content;

	new_content = ft_calloc(1, sizeof(t_kv));
	if (new_content == NULL)
		return (NULL);
	new_content->key = ft_strdup(content->key);
	new_content->value = ft_strdup(content->value);
	if (new_content->key == NULL || new_content->value == NULL)
		return (free_kv(new_content), NULL);
	return (new_content);
}

t_list	*copy_env_list(t_list **env)
{
	t_list	*new_list;
	t_list	*current;
	t_list	*new_node;
	t_kv	*new_content;

	new_list = NULL;
	current = *env;
	while (current)
	{
		new_content = copy_env_content(current->content);
		if (new_content == NULL)
			return (list_clear(&new_list, free_kv), NULL);
		new_node = list_new(new_content);
		if (new_node == NULL)
			return (free_kv(new_content), list_clear(&new_list, free_kv), NULL);
		list_add_back(&new_list, new_node);
		current = current->next;
	}
	return (new_list);
}
