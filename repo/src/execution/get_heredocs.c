/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_heredocs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 23:02:27 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/08 22:56:02 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	get_heredoc_readline(t_tree *current, int pipe_[2], t_data *data)
{
	char	*line;

	line = readline("heredoc> ");
	if (line == NULL)
		return (close_2(pipe_), error_exit(READLINE, data));
	while (ft_strcmp(line, get_content(current->left)) != 0)
	{
		write(pipe_[1], line, ft_strlen(line));
		write(pipe_[1], "\n", 1);
		free(line);
		line = readline("heredoc> ");
		if (line == NULL)
			return (close_2(pipe_), error_exit(READLINE, data));
	}
	free(line);
}

static void	get_heredocs_cmd(t_tree **tree, t_data *data)
{
	int		pipe_[2];
	t_tree	*current;

	current = *tree;
	while (is_broket(current))
	{
		if (get_type(current) == T_DOUBLE_BROKET_LEFT)
		{
			if (pipe(pipe_))
				error_exit(PIPE, data);
			get_heredoc_readline(current, pipe_, data);
			close(pipe_[1]);
			((t_token *)((t_list *)((current)->content))->content)->here_doc \
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
		get_heredocs_cmd(&(*tree)->right, data);
		get_heredocs(&(*tree)->left, data);
	}
	else
		get_heredocs_cmd(tree, data);
}
