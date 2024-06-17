/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:12:57 by qhauuy            #+#    #+#             */
/*   Updated: 2024/06/17 17:14:36 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	run_cmd(t_data *data, int in, int out)
{
	if (dup2(in, 0) == -1)
		error_exit(DUP, data);
	if (dup2(out, 1) == -1)
		error_exit(DUP, data);
	if (execve(data->cmd->pathname, data->cmd->argv, NULL) == -1)
	{
		print_error(EXEC);
		free_all(data);
		exit(0);
		// error_exit(EXEC, data);
	}
}

int	get_redirections(t_tree **tree, t_data *data)
{
	if (get_type(*tree) != T_BROKET_LEFT
		&& get_type(*tree) != T_BROKET_RIGHT
		&& get_type(*tree) != T_DOUBLE_BROKET_RIGHT)
		return (0);
	if (get_type(*tree) == T_BROKET_LEFT)
	{
		if (data->in != 0)
			close(data->in);
		data->in = open(get_content((*tree)->left), O_RDONLY);
		printf("data->in = %d\n", data->in);
		if (data->in == -1)
			return (fd_error(get_content((*tree)->left), data), 1);
	}
	else if (get_type(*tree) == T_BROKET_RIGHT)
	{
		if (data->out != 1)
			close(data->out);
		data->out = open(\
			get_content((*tree)->left), O_WRONLY | O_CREAT | O_TRUNC, 0644);
		printf("data->out = %d\n", data->out);
		if (data->out == -1)
			return (fd_error(get_content((*tree)->left), data), 1);
	}
	else if (get_type(*tree) == T_DOUBLE_BROKET_RIGHT)
	{
		if (data->out != 1)
			close(data->out);
		data->out = open(\
			get_content((*tree)->left), O_WRONLY | O_CREAT | O_APPEND, 0644);
		printf("data->out = %d\n", data->out);
		if (data->out == -1)
			return (fd_error(get_content((*tree)->left), data), 1);
	}
	*tree = (*tree)->right;
	return (get_redirections(tree, data));
}

/*
si le noeud est un pipe
creer un pipe
creer 2 fils
pour un fils
	init struct de commandes
	init redirections

redirections
fils droit
	in : pipe[0]
	out : data->fd_out
fils gauche
	in : data->fd_in
	out : pipe[1]
*/
void	exec(t_tree *tree, t_data *data)
{
	pid_t		pid;

	if (data->ast == NULL)
		return ;

	if (get_type(tree) == T_PIPE)
	{

	}
	else
	{
		printf("data->in = %d\n", data->in);
		printf("data->out = %d\n", data->out);
		if (get_redirections(&tree, data))
			return ;
		printf("data->in = %d\n", data->in);
		printf("data->out = %d\n", data->out);
		pid = fork();
		if (pid == -1)
			error_exit(FORK, data);
		else if (pid == 0)
		{
			get_cmd(data, tree);
			print_cmd(data->cmd);
			run_cmd(data, data->in, data->out);
		}
		waitpid(pid, NULL, 0);
	}
}



/*HereDoc


quand on a l'ast
on parcourt recursivement l'arbre de gauche a droite

si on a un << et que le read_write du noeud est a 0, on cree un pipe, on readline jusqu'a obtenir le delimiteur (strcmp du fils gauche par rapport a l'input de readline), on transfert le contenu du read_write du fils droit et on continue tant qu'on a des heredoc
(on ferme le pipe en lecture)
quand on est sur une commande, si read_write nest pas a 0, on remplace son stdin par le read du read_write
(on ferme le pipe en ecriture)

+
*/
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
			//
			exec(data.ast, &data);
			reset_input(&data);
		}
	}
	return (free_all(&data), 0);
}
