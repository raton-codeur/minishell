/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:12:57 by qhauuy            #+#    #+#             */
/*   Updated: 2024/06/22 19:48:18 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"


void	run_cmd(t_data *data)
{
	dup2(data->in, 0);
	dup2(data->out, 1);
	if (execve(data->cmd->pathname, data->cmd->argv, NULL) == -1)
	{
		perror("execve");
		free_all(data);
		exit(0);
	}
}

void	exec_cmd(t_tree *tree, t_data *data)
{
	if (set_redirections(&tree, data))
		return ;
	get_cmd(tree, data);
	run_cmd(data);
}

void	exec_pipe(t_tree *tree, t_data *data)
{
	pid_t	pid1;
	pid_t	pid2;
	int		pipe_[2];

	pipe(pipe_);
	pid1 = fork();
	if (pid1 == 0)
	{
		data->in = pipe_[0];
		close(pipe_[1]);
		exec_cmd(tree->right, data);
	}
	pid2 = fork();
	if (pid2 == 0)
	{
		data->out = pipe_[1];
		close(pipe_[0]);
		exec_cmd(tree->left, data);
	}
	close(pipe_[0]);
	close(pipe_[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	exit(0);
}

void	exec(t_tree *tree, t_data *data)
{
	pid_t	pid;

	if (data->ast == NULL)
		return ;
	pid = fork();
	if (pid == 0)
	{
		if (get_type(tree) == T_PIPE)
			exec_pipe(tree, data);
		else
			exec_cmd(tree, data);
	}
	waitpid(pid, NULL, 0);
}




void	get_here_doc(t_tree **tree, t_data *data, int pipe_[2])
{
	char	*line;
	t_tree	*current;

	current = *tree;
	while (get_type(current) == T_DOUBLE_BROKET_LEFT)
	{
		line = readline("heredoc> ");
		if (line == NULL)
			error_exit(READ_LINE, data);
		while (ft_strcmp(line, get_content(current->left)) != 0)
		{
			write(pipe_[1], line, ft_strlen(line));
			write(pipe_[1], "\n", 1);
			free(line);
			line = readline("heredoc> ");
			if (line == NULL)
				error_exit(READ_LINE, data);
		}
		free(line);
		current = current->right;
	}
	close(pipe_[1]);
	if (current == NULL)
		close(pipe_[0]);
	else
		((t_token *)((t_list *)(current->content))->content)->here_doc \
			= pipe_[0];
}

void	get_here_docs(t_tree **tree, t_data *data)
{
	int		pipe_[2];

	if (*tree == NULL)
		return ;
	if (get_type(*tree) == T_DOUBLE_BROKET_LEFT)
	{
		if (pipe(pipe_) == -1)
			error_exit(PIPE, data);
		get_here_doc(tree, data, pipe_);
	}
	else if (get_type(*tree) == T_PIPE)
	{
		get_here_docs(&(*tree)->left, data);
		get_here_docs(&(*tree)->right, data);
	}
}

int	main(void)
{
	t_data	data;

	init_data(&data);
	while (1)
	{
		data.input = readline("minishell> ");
		if (data.input == NULL)
			return (error_exit(READ_LINE, &data), 1);
		else
		{
			if (ft_strcmp(data.input, "exit") == 0)
				return (free_all(&data), 0);
			if (data.input[0] != '\0' && !ft_strisspace(data.input))
				add_history(data.input);
			get_tokens(&data);
			lexing(&data);
			init_ast(&data);
			build_tree(&data.ast, &data);
			tree_print(data.ast);
			get_here_docs(&data.ast, &data);
			exec(data.ast, &data);
			reset_input(&data);
		}
	}
	return (free_all(&data), 0);
}
