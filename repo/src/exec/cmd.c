/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 22:00:11 by qhauuy            #+#    #+#             */
/*   Updated: 2024/06/25 16:24:55 by qhauuy           ###   ########.fr       */
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
			error_exit(MALLOC, data);
		if (access(result, X_OK) == 0)
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
	return (1 + get_argc(tree->left));
}

void	prepare_exec(t_tree *tree, t_data *data)
{
	int		argc;
	int		i;

	if (tree == NULL)
		return ;
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






int	has_slash(char *s)
{
	while (*s)
	{
		if (*s == '/')
			return (1);
		s++;
	}
	return (0);
}



void	analyse_file(char *name, t_data *data)
{
	(void)data;
	if (access(name, F_OK) == -1)
	{
		printf("file not found\n");
	}
	else
		printf("file found\n");
}





void	analyse_cmd(t_tree *tree, t_data *data)
{
	if (has_slash(get_content(tree)))
		analyse_file(get_content(tree), data);
	else
		prepare_exec(tree, data);
}

