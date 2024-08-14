/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 16:26:24 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/17 18:30:54 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(int code)
{
	if (code == MALLOC)
		ft_putstr_fd("minishell: memory allocation error\n", 2);
	else if (code == READLINE)
		perror("minishell: readline");
	else if (code == LEXING)
		ft_putstr_fd("minishell: lexical error\n", 2);
	else if (code == QUOTE)
		ft_putstr_fd("minishell: invalid quotes\n", 2);
	else if (code == PIPE)
		perror("pipe");
	else if (code == FORK)
		perror("fork");
	else if (code == SIGACTION)
		perror("sigaction");
	else if (code == PWD)
		perror("minishell: pwd");
}

void	error_exit(int code, t_data *data)
{
	print_error(code);
	free_all(data);
	exit(1);
}

void	syntax_error(char *token, t_data *data)
{
	char	*message;
	char	*message_join;

	message = ft_strjoin(\
		"minishell: syntax error near unexpected token `", token);
	if (message == NULL)
		error_exit(MALLOC, data);
	message_join = ft_strjoin(message, "'\n");
	free(message);
	if (message_join == NULL)
		error_exit(MALLOC, data);
	ft_putstr_fd(message_join, 2);
	free(message_join);
	free_input(data);
	g_exit_status = 2;
}

void	fd_error(char *file, t_data *data)
{
	ft_putstr_fd("minishell: ", 2);
	perror(file);
	free_all(data);
	exit(1);
}
