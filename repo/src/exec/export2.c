/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteste <jteste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:32:56 by jteste            #+#    #+#             */
/*   Updated: 2024/07/04 16:55:29 by jteste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	export_error(char **key, char **value)
{
	printf("minishell: export: `%s': not a valid identifier\n", *key);
	if (*key)
		free(*key);
	if (*value)
		free(*value);
}

t_envp	*creat_full_env_node(char *arg)
{
	t_envp	*new_content;
	char	**split;

	new_content = ft_calloc(1, sizeof(t_envp));
	if (new_content == NULL)
		return (NULL);
	split = ft_split_once(arg, '=');
	if (split == NULL)
	{
		free(new_content);
		return (NULL);
	}
	new_content->key = split[0];
	new_content->value = split[1];
	free(split);
	return (new_content);
}

t_envp	*creat_half_env_node(char *arg)
{
	t_envp	*new_content;

	new_content = ft_calloc(1, sizeof(t_envp));
	if (new_content == NULL)
		return (NULL);
	new_content->key = ft_strdup(arg);
	new_content->value = ft_strdup("");
	if (new_content->key == NULL || new_content->value == NULL)
	{
		free(new_content->key);
		free(new_content->value);
		free(new_content);
		return (NULL);
	}
	return (new_content);
}

static t_envp	*copy_env_content(t_envp *content)
{
	t_envp	*new_content;

	new_content = ft_calloc(1, sizeof(t_envp));
	if (new_content == NULL)
		return (NULL);
	new_content->key = ft_strdup(content->key);
	new_content->value = ft_strdup(content->value);
	if (new_content->key == NULL || new_content->value == NULL)
	{
		free(new_content->key);
		free(new_content->value);
		free(new_content);
		return (NULL);
	}
	return (new_content);
}

t_list	*copy_env_list(t_list **envp)
{
	t_list	*new_list;
	t_list	*current;
	t_list	*new_node;
	t_envp	*new_content;

	new_list = NULL;
	current = *envp;
	while (current)
	{
		new_content = copy_env_content(current->content);
		if (new_content == NULL)
			return (NULL);
		new_node = list_new(new_content);
		if (new_node == NULL)
			return (NULL);
		list_add_back(&new_list, new_node);
		current = current->next;
	}
	return (new_list);
}
