/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_heredocs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 23:02:27 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/14 16:56:50 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	is_delimiter(char *line, char *delimiter)
{
	if (ft_strchr(line, '\n'))
		*strchr(line, '\n') = '\0';
	return (ft_strcmp(line, delimiter) == 0);
}

static void	get_heredoc(char *delimiter, int pipe_[2], t_data *data)
{
	char	*line;

	ft_putstr_fd("heredoc >>> ", 1);
	errno = 0;
	line = get_next_line(0);
	if (line == NULL && errno)
		heredoc_error(pipe_, data);
	while (line && !is_delimiter(line, delimiter))
	{
		line[ft_strlen(line)] = '\n';
		write(pipe_[1], line, ft_strlen(line));
		free(line);
		ft_putstr_fd("heredoc >>> ", 1);
		line = get_next_line(0);
		if (line == NULL && errno)
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
			close(pipe_[1]);
			((t_token *)((t_list *)((current)->content))->content)->here_doc
				= pipe_[0];
		}
		current = current->right;
	}
}

void	get_heredocs(t_tree **tree, t_data *data)
{
	if (*tree == NULL)
		return ;
	if (get_type(*tree) == T_PIPE)
	{
		get_heredocs(&(*tree)->left, data);
		get_heredocs_cmd(&(*tree)->right, data);
	}
	else
		get_heredocs_cmd(tree, data);
}
