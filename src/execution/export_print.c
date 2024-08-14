/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 16:29:29 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/17 16:29:37 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	export_print_content(void *p)
{
	t_kv	*kv;

	kv = p;
	if (kv->value == NULL)
		printf("declare -x %s\n", kv->key);
	else
		printf("declare -x %s=\"%s\"\n", kv->key, kv->value);
}

static t_kv	*get_copy_content(t_kv *content)
{
	t_kv	*result;

	result = ft_calloc(1, sizeof(t_kv));
	if (result == NULL)
		return (NULL);
	result->key = ft_strdup(content->key);
	if (content->value != NULL)
	{
		result->value = ft_strdup(content->value);
		if (result->value == NULL)
			return (free_kv(result), NULL);
	}
	if (result->key == NULL)
		return (free_kv(result), NULL);
	return (result);
}

t_list	*get_copy_list(t_list **env)
{
	t_list	*result;
	t_list	*current;
	t_list	*new_node;
	t_kv	*new_content;

	result = NULL;
	current = *env;
	while (current)
	{
		new_content = get_copy_content(current->content);
		if (new_content == NULL)
			return (list_clear(&result, free_kv), NULL);
		new_node = list_new(new_content);
		if (new_node == NULL)
			return (free_kv(new_content), list_clear(&result, free_kv), NULL);
		list_add_back(&result, new_node);
		current = current->next;
	}
	return (result);
}

static void	sort(t_list **env)
{
	t_list	*current;
	t_list	*next;
	t_kv	*tmp;

	current = *env;
	while (current)
	{
		next = current->next;
		while (next)
		{
			if (ft_strcmp(((t_kv *)current->content)->key,
					((t_kv *)next->content)->key) > 0)
			{
				tmp = current->content;
				current->content = next->content;
				next->content = tmp;
			}
			next = next->next;
		}
		current = current->next;
	}
}

void	export_print(t_data *data)
{
	t_list	*copy;

	copy = get_copy_list(&data->env);
	sort(&copy);
	list_print(copy, export_print_content);
	list_clear(&copy, free_kv);
}
