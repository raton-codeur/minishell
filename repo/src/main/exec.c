/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:12:57 by qhauuy            #+#    #+#             */
/*   Updated: 2024/06/20 17:38:58 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	run_cmd(t_data *data, int in, int out)
{
	dup2(in, 0);
	dup2(out, 1);
	if (execve(data->cmd->pathname, data->cmd->argv, NULL) == -1)
	{
		perror("execve");
		reset_input(data);
		exit(0);
	}
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
		// printf("avant get redirections : \n in : %d\nout : %d\n", data->in, data->out);
		if (set_redirections(&tree, data))
			return ;
		// printf("apres get redirections : \n in : %d\nout : %d\n", data->in, data->out);
		pid = fork();
		if (pid == 0)
		{
			get_cmd(tree, data);
			// print_cmd(data->cmd);
			run_cmd(data, data->in, data->out);
		}
		waitpid(pid, NULL, 0);
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
			exec(data.ast, &data);
			reset_input(&data);
		}
	}
	return (free_all(&data), 0);
}
