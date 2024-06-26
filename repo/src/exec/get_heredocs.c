/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_heredocs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteste <jteste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 23:02:27 by qhauuy            #+#    #+#             */
/*   Updated: 2024/06/26 12:49:58 by jteste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	get_heredoc_readline(t_tree *current, int pipe_[2])
{
	char	*line;

	line = readline("heredoc> ");
	if (line == NULL)
		return (close_2(pipe_), error_exit(READLINE));
	while (ft_strcmp(line, get_content(current->left)) != 0)
	{
		write(pipe_[1], line, ft_strlen(line));
		write(pipe_[1], "\n", 1);
		mmm_free(line);
		line = readline("heredoc> ");
		if (line == NULL)
			return (close_2(pipe_), error_exit(READLINE));
	}
	mmm_free(line);
}

static void	get_heredoc(t_tree **tree)
{
	int		pipe_[2];
	t_tree	*current;

	if (pipe(pipe_))
		error_exit(PIPE);
	current = *tree;
	while (is_broket(current))
	{
		if (get_type(current) == T_DOUBLE_BROKET_LEFT)
			get_heredoc_readline(current, pipe_);
		current = current->right;
	}
	close(pipe_[1]);
	if (current == NULL)
		close(pipe_[0]);
	else
		((t_token *)((t_list *)(current->content))->content)->here_doc \
			= pipe_[0];
}

static int	has_heredoc(t_tree *tree)
{
	if (tree == NULL)
		return (0);
	return (get_type(tree) == T_DOUBLE_BROKET_LEFT || has_heredoc(tree->right));
}

void	get_heredocs(t_tree **tree, t_data *data)
{
	if (*tree == NULL)
		return ;
	if (get_type(*tree) == T_PIPE)
	{
		get_heredocs(&(*tree)->left, data);
		get_heredocs(&(*tree)->right, data);
	}
	else if (has_heredoc(*tree))
		get_heredoc(tree);
}
