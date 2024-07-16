/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:00:46 by jteste            #+#    #+#             */
/*   Updated: 2024/07/16 16:57:31 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	print_export_content(void *p)
{
	t_kv	*kv;

	kv = p;
	if (kv->value == NULL)
		printf("declare -x %s\n", kv->key);
	else
		printf("declare -x %s=\"%s\"\n", kv->key, kv->value);
}

void	export_error(t_list *new, t_data *data)
{
	if (data->cmd->argc == 2)
		printf("minishell: export: `%s': not a valid identifier\n", data->cmd->argv[1]);
	else
		printf("minishell: export: `%s': not a valid identifier\n", get_key(new));
	list_remove_node(&data->env, new, free_kv);
	g_exit_status = 1;
}

static t_kv	*copy_env_content(t_kv *content)
{
	t_kv	*new_content;

	new_content = ft_calloc(1, sizeof(t_kv));
	if (new_content == NULL)
		return (NULL);
	new_content->key = ft_strdup(content->key);
	if (content->value != NULL)
	{
		new_content->value = ft_strdup(content->value);
		if (new_content->value == NULL)
			return (free_kv(new_content), NULL);
	}
	if (new_content->key == NULL)
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

static void	sort_export_list(t_list **env)
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

static void	export_print(t_list **envp)
{
	t_list	*current;

	current = copy_env_list(envp);
	sort_export_list(&current);
	list_print(current, print_export_content);
	list_clear(&current, free_kv);
}

static void	add_export_variable(t_data *data)
{
	int		i;
	t_list	*new;

	i = 1;
	while (i < data->cmd->argc)
	{
		new = insert_in_env(data->cmd->argv[i], data);
		if ((ft_isword_start(get_key(new)[0]) == 0) || (ft_strchr(get_key(new), ' ') != NULL)) 
			export_error(new, data);
		else
			g_exit_status = 0;
		i++;
	}
}

void	export_(t_tree *tree, t_data *data, int in_parent)
{
	prepare_execution_relative(tree, data);
	if (data->cmd->argc == 1)
	{
		export_print(&data->env);
		finish_builtin(in_parent, g_exit_status, data);
	}
	else
		add_export_variable(data);
	finish_builtin(in_parent, g_exit_status, data);
}
