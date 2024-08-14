/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:33:17 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/17 17:54:32 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static char	*get_pathname(char *name, t_data *data)
{
	char		*result;
	int			i;
	struct stat	sb;

	result = NULL;
	i = 0;
	if (data->path == NULL)
		return (cmd_pathname_error(name, data), NULL);
	while (data->path[i])
	{
		result = ft_strjoin(data->path[i], name);
		if (result == NULL)
			error_exit(MALLOC, data);
		if (stat(result, &sb) == 0
			&& !S_ISDIR(sb.st_mode) && access(result, X_OK) == 0)
			return (result);
		free(result);
		i++;
	}
	cmd_pathname_error(name, data);
	return (NULL);
}

static int	get_argc(t_tree *tree)
{
	if (tree == NULL)
		return (0);
	return (1 + get_argc(tree->right));
}

static void	prepare_argv(t_tree *tree, t_data *data)
{
	int		i;

	if (tree == NULL)
		return ;
	data->cmd = ft_calloc(1, sizeof(t_cmd));
	if (data->cmd == NULL)
		error_exit(MALLOC, data);
	data->cmd->argc = get_argc(tree);
	data->cmd->argv = ft_calloc(data->cmd->argc + 1, sizeof(char *));
	if (data->cmd->argv == NULL)
		error_exit(MALLOC, data);
	i = 0;
	while (i < data->cmd->argc)
	{
		data->cmd->argv[i++] = get_content(tree);
		tree = tree->right;
	}
	data->cmd->argv[i] = NULL;
}

void	prepare_execution_absolute(t_tree *tree, t_data *data)
{
	prepare_argv(tree, data);
	data->cmd->pathname = get_pathname(data->cmd->argv[0], data);
}

void	prepare_execution_relative(t_tree *tree, t_data *data)
{
	prepare_argv(tree, data);
	data->cmd->pathname = ft_strdup(data->cmd->argv[0]);
	if (data->cmd->pathname == NULL)
		error_exit(MALLOC, data);
}
