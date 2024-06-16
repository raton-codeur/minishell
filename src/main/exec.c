/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:12:57 by qhauuy            #+#    #+#             */
/*   Updated: 2024/06/16 17:18:03 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// void	new_pipe(t_data *data)
// {

// }

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
// void	exec_tree(t_tree **tree, t_data *data)
// {
// 	t_iterable	current;

// 	if (!*tree)
// 		return ;
// 	set_iterable(&current, (*tree)->content);
// 	if (current.type == T_PIPE)
// 	{
// 		new_pipe(data);

// 	}
// }


// int	main(void)
// {
// 	t_data	data;

// 	init_data(&data);
// 	while (1)
// 	{
// 		data.input = readline("minishell> ");
// 		if (data.input == NULL)
// 			return (error_exit(READ_LINE, &data), 1);
// 		else
// 		{
// 			if (ft_strcmp(data.input, "exit") == 0)
// 				return (free_all(&data), 0);
// 			if (data.input[0] != '\0' && !ft_strisspace(data.input))
// 				add_history(data.input);

// 			get_tokens(&data);
// 			if (lexing(&data))
// 			{
// 				init_ast(&data);
// 				if (build_tree(&data.ast, &data))
// 				{
// 					tree_print(data.ast);
// 					exec_tree(&data.ast, &data);
// 				}
// 			}
// 			reset_input(&data);
// 		}
// 	}
// 	return (free_all(&data), 0);
// }
