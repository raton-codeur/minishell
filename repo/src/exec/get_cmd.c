/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteste <jteste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 22:00:11 by qhauuy            #+#    #+#             */
/*   Updated: 2024/06/26 12:48:46 by jteste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/*
si le fichier existe mais que le droit nest pas bon -> code 126

si le name contient un slash -> regarder si le fichier existe directement sans regarder le path
*/
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
			error_exit(MALLOC);
		if (access(result, X_OK) == 0)
			return (result);
		mmm_free(result);
		i++;
	}
	cmd_name_error(name);
	return (NULL);
}

static int	get_argc(t_tree *tree)
{
	if (tree == NULL)
		return (0);
	return (1 + get_argc(tree->left));
}

void	get_cmd(t_tree *tree, t_data *data)
{
	int		argc;
	int		i;

	if (tree == NULL)
		return ;
	data->cmd = mmm_malloc(1 * sizeof(t_cmd));
	if (data->cmd == NULL)
		error_exit(MALLOC);
	argc = get_argc(tree);
	data->cmd->argv = mmm_malloc((argc + 1) * sizeof(char *));
	if (data->cmd->argv == NULL)
		error_exit(MALLOC);
	i = 0;
	while (i < argc)
	{
		data->cmd->argv[i++] = get_content(tree);
		tree = tree->left;
	}
	data->cmd->argv[i] = NULL;
	data->cmd->pathname = get_pathname(data->cmd->argv[0], data);
}
