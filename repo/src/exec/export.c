/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteste <jteste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:00:46 by jteste            #+#    #+#             */
/*   Updated: 2024/07/04 17:21:49 by jteste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	sort_export_list(t_list **envp)
{
	t_list	*current;
	t_list	*next;
	t_envp	*tmp;

	current = *envp;
	while (current)
	{
		next = current->next;
		while (next)
		{
			if (ft_strcmp(((t_envp *)current->content)->key,
					((t_envp *)next->content)->key) > 0)
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

static void	print_export(t_list **envp)
{
	t_list	*current;

	current = copy_env_list(envp);
	sort_export_list(&current);
	list_print(current, print_export_content);
	list_clear(&current, free_env);
}

static int	add_env(t_list **envp, t_envp *new)
{
	t_list	*new_node;

	new_node = list_new(new);
	if (new_node == NULL)
		return (1);
	list_add_back(envp, new_node);
	return (0);
}

static void	add_export_variable(t_data *data)
{
	int		i;
	t_envp	*new;

	i = 1;
	while (i < data->cmd->argc)
	{
		if (ft_strchr(data->cmd->argv[i], '=')
			&& ft_strchr(data->cmd->argv[i], '=') != data->cmd->argv[i])
			new = creat_full_env_node(data->cmd->argv[i]);
		else
			new = creat_half_env_node(data->cmd->argv[i]);
		if (new == NULL || new->key == NULL || new->value == NULL)
			error_exit(MALLOC, data);
		if (ft_isword_start(new->key[0]) == 0)
			return (export_error(&new->key, &new->value));
		if (find_env_key(&data->envp, new->key) == NULL)
			add_env(&data->envp, new);
		else
		{
			modify_key_value(&data->envp, new->key, new->value);
			free_env(new);
		}
		i++;
	}
}

void	export_(t_tree *tree, t_data *data, int in_parent)
{
	prepare_exec_relative(tree, data);
	if (data->cmd->argc == 1)
	{
		print_export(&data->envp);
		if (!in_parent)
			return (free_all(data), exit(0));
	}
	else
		add_export_variable(data);
	if (!in_parent)
		return (free_all(data), exit(0));
}
