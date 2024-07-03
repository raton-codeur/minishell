/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteste <jteste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:00:46 by jteste            #+#    #+#             */
/*   Updated: 2024/07/03 16:00:41 by jteste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	sort_export_list(t_list **envp)
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

void	print_export(t_list **envp)
{
	t_list	*current;
	char	*buff;
	char	*join;

	current = *envp;
	sort_export_list(&current);
	while (current)
	{
		buff = ft_strjoin("declare -x ", ((t_envp *)current->content)->key);
		join = ft_strjoin(buff, "=\"");
		free(buff);
		buff = ft_strjoin(join, ((t_envp *)current->content)->value);
		free(join);
		join = ft_strjoin(buff, "\"\n");
		free(buff);
		printf("%s", join);
		free(join);
		current = current->next;
	}
}

int	add_env(t_list **envp, char *key, char *value)
{
	t_envp	*new_content;
	t_list	*new_node;

	new_content = ft_calloc(1, sizeof(t_envp));
	if (new_content == NULL)
		return (1);
	new_content->key = key;
	new_content->value = value;
	new_node = list_new(new_content);
	if (new_node == NULL)
		return (1);
	list_add_back(envp, new_node);
	return (0);
}

int	add_export_variable(t_tree *tree, t_data *data, int in_parent)
{
	int		i;
	char	*key;
	char	*value;
	char	**tmp;

	(void)in_parent;
	(void)tree;
	i = 1;
	while (i < data->cmd->argc)
	{
		if (ft_strchr(data->cmd->argv[i], '='))
		{
			tmp = ft_split_once(data->cmd->argv[i], '=');
			key = ft_strdup(tmp[0]);
			value = ft_strdup(tmp[1]);
			deep_free((void **)tmp, 2);
		}
		else
		{
			key = ft_strdup(data->cmd->argv[i]);
			value = ft_strdup("");
		}
		if (key == NULL || value == NULL)
			error_exit(MALLOC, data);
		if (ft_isword_start(key[0]) == 0)
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(key, 2);
			ft_putendl_fd("': not a valid identifier", 2);
			free(key);
			free(value);
			return (1);
		}
		if (find_env_key(&data->envp, key) == NULL)
			add_env(&data->envp, key, value);
		else
		{
			modify_key_value(&data->envp, key, value);
			free(key);
			free(value);
		}
		i++;
	}
	return (0);
}

int	export_(t_tree *tree, t_data *data, int in_parent)
{
	prepare_exec_relative(tree, data);
	if (data->cmd->argc == 1)
	{
		print_export(&data->envp);
		return (0);
	}
	else
		add_export_variable(tree->left, data, in_parent);
	if (!in_parent)
		exit(0);
	return (0);
}
