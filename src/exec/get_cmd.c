/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 22:00:11 by qhauuy            #+#    #+#             */
/*   Updated: 2024/06/17 14:01:17 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static char	*get_pathname(char *name, t_data *data)
{
	char	*result;
	int		i;

	result = NULL;
	i = 0;
	if (data->path == NULL)
		return (NULL);
	while (data->path[i])
	{
		result = ft_strjoin(data->path[i], name);
		if (result == NULL)
			error_exit(MALLOC, data);
		if (access(result, X_OK) == 0)
			return (result);
		free(result);
		i++;
	}
	result = ft_strdup(name);
	if (result == NULL)
		error_exit(MALLOC, data);
	return (result);
}

static int	get_argc(t_tree *tree)
{
	if (tree == NULL)
		return (0);
	return (1 + get_argc(tree->left));
}

void	get_cmd(t_data *data, t_tree *tree)
{
	int		argc;
	int		i;

	data->cmd = ft_calloc(1, sizeof(t_cmd));
	if (data->cmd == NULL)
		error_exit(MALLOC, data);
	argc = get_argc(tree);
	data->cmd->argv = ft_calloc(argc + 1, sizeof(char *));
	if (data->cmd->argv == NULL)
		error_exit(MALLOC, data);
	i = 0;
	while (i < argc)
	{
		data->cmd->argv[i++] = get_content(tree);
		tree = tree->left;
	}
	data->cmd->argv[i] = NULL;
	data->cmd->pathname = get_pathname(data->cmd->argv[0], data);
}
