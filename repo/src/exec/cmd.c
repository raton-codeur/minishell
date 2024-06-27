/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 22:00:11 by qhauuy            #+#    #+#             */
/*   Updated: 2024/06/27 12:29:38 by qhauuy           ###   ########.fr       */
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

void	prepare_argv(t_tree *tree, t_data *data)
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
}

void	prepare_exec_absolute(t_tree *tree, t_data *data)
{
	prepare_argv(tree, data);
	data->cmd->pathname = get_pathname(data->cmd->argv[0], data);
}

void	prepare_exec_relative(t_tree *tree, t_data *data)
{
	prepare_argv(tree, data);
	data->cmd->pathname = ft_strdup(data->cmd->argv[0]);
	if (data->cmd->pathname == NULL)
		error_exit(MALLOC, data);
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

void	file_error(char *name, t_data *data)
{
	ft_putstr_fd("minishell: ", 2);
	perror(name);
	free_all(data);
	exit(1);
}

void	analyse_file(t_tree *tree, t_data *data)
{
	struct stat	sb;
	char		*name;

	name = get_content(tree);
	if (stat(name, &sb) == -1)
		file_error(name, data);
		/* mettre le code derreur a 127*/
	if (S_ISDIR(sb.st_mode))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(name, 2);
		ft_putendl_fd(": Is a directory", 2);
		free_all(data);
		exit(1);
		/* mettre le code derreur a 126 */
	}
	if (access(name, R_OK | X_OK) == -1)
		file_error(name, data);
		/* mettre le code derreur a 126 */
	else
	{
		prepare_exec_relative(tree, data);
		// printf("file found et ok\n");
	}
}

void	analyse_cmd(t_tree *tree, t_data *data)
{
	if (has_slash(get_content(tree)))
		analyse_file((tree), data);
	else
		prepare_exec_absolute(tree, data);
}
