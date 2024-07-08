/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:00:46 by jteste            #+#    #+#             */
/*   Updated: 2024/07/08 17:36:45 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

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

static void	print_export(t_list **envp)
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
		new = add_to_env(data->cmd->argv[i], data);
		if (ft_isword_start(get_key(new)[0]) == 0)
		{
			printf("key : %s\n", get_key(new));
			return (export_error(new, data));
		}
		i++;
	}
}

int	export_(t_tree *tree, t_data *data, int in_parent)
{
	prepare_exec_relative(tree, data);
	if (data->cmd->argc == 1)
	{
		print_export(&data->env);
		end_builtin(in_parent, 0, data);
	}
	else
		add_export_variable(data);
	return (end_builtin(in_parent, 0, data));
}
