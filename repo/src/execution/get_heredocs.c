/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_heredocs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 23:02:27 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/14 14:13:45 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	get_heredoc(char *delimiter, int pipe_[2], t_data *data)
{
	char	*line;

	printf("---------------\nerrno avant printf %d\n", errno);
	printf("heredoc> ");
	line = get_next_line(0);
	printf("errno apres gnl %d\n----------------\n", errno);
	if (line == NULL && errno)
		return (close_2(pipe_), error_exit(READLINE, data));
	else if (line == NULL)
		return ;
	while (ft_strcmp(line, delimiter) != 0)
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
	while (get_broket(current->content))
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
		get_heredocs_cmd(&(*tree)->right, data);
		get_heredocs(&(*tree)->left, data);
	}
	else
		get_heredocs_cmd(tree, data);
}
