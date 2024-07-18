/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_heredocs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 23:02:27 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/19 00:12:05 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	is_delimiter(char *line, char *delimiter)
{
	int	result;

	if (ft_strchr(line, '\n'))
	{
		line[ft_strlen(line) - 1] = '\0';
		result = ft_strcmp(line, delimiter) == 0;
		line[ft_strlen(line)] = '\n';
		return (result);
	}
	else
		return (ft_strcmp(line, delimiter) == 0);
}

static void	get_heredoc(char *delimiter, int pipe_[2], t_data *data)
{
	char	*line;

	g_exit_status = 0;
	ft_putstr_fd("heredoc >>> ", 1);
	errno = 0;
	line = get_next_line(0);
	if (g_exit_status == 130)
		return (free(line), free_input(data));
	if (line == NULL && errno && errno != EINTR)
		heredoc_error(pipe_, data);
	while (line && !is_delimiter(line, delimiter))
	{
		write(pipe_[1], line, ft_strlen(line));
		free(line);
		ft_putstr_fd("heredoc >>> ", 1);
		line = get_next_line(0);
		if (g_exit_status == 130)
			return (free(line), free_input(data));
		if (line == NULL && errno && errno != EINTR)
			return (heredoc_error(pipe_, data));
	}
	if (line == NULL)
		ft_putchar_fd('\n', 1);
	free(line);
}

static void	get_heredocs_cmd(t_tree **tree, t_data *data)
{
	int		pipe_[2];
	t_tree	*current;

	current = *tree;
	while (current && get_broket(current->content))
	{
		if (get_type(current) == T_DOUBLE_BROKET_LEFT)
		{
			if (pipe(pipe_))
				error_exit(PIPE, data);
			get_heredoc(get_content(current->left), pipe_, data);
			if (data->ast == NULL)
				return ;
			close(pipe_[1]);
			((t_token *)((t_list *)((current)->content))->content)->here_doc
				= pipe_[0];
		}
		current = current->right;
	}
}

static void	get_heredocs_rec(t_tree **tree, t_data *data)
{
	if (*tree == NULL)
		return ;
	if (get_type(*tree) == T_PIPE)
	{
		get_heredocs_rec(&(*tree)->left, data);
		if (*tree)
			get_heredocs_cmd(&(*tree)->right, data);
	}
	else
		get_heredocs_cmd(tree, data);
}

void	get_heredocs(t_tree **tree, t_data *data)
{
	int	save;

	save = g_exit_status;
	g_exit_status = 0;
	set_heredoc_signals();
	get_heredocs_rec(tree, data);
	if (g_exit_status == 130)
		ft_putchar_fd('\n', 2);
	else
		g_exit_status = save;
	set_parent_signals();
}
