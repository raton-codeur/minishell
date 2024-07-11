/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteste <jteste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 16:26:24 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/11 16:20:38 by jteste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(int code)
{
	if (code != DEFAULT)
		ft_putstr_fd("minishell: ", 2);
	if (code == MALLOC)
		ft_putendl_fd("memory allocation error", 2);
	else if (code == READLINE)
		ft_putendl_fd("readline failed", 2);
	else if (code == LEXING)
		ft_putendl_fd("lexical error", 2);
	else if (code == QUOTE)
		ft_putendl_fd("invalid quotes", 2);
	else if (code == PIPE)
		ft_putendl_fd("pipe failed", 2);
	else if (code == FORK)
		ft_putendl_fd("fork failed", 2);
	else if (code == EXIT)
		ft_putendl_fd("exit", 1);
}

void	error(int code, t_data *data)
{
	print_error(code);
	reset_input(data);
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

	message = ft_strjoin("minishell: syntax error near unexpected token `", token);
	if (!message)
		error_exit(MALLOC, data);
	message_join = ft_strjoin(message, "'");
	free(message);
	if (!message_join)
		error_exit(MALLOC, data);
	ft_putendl_fd(message_join, 2);
	free(message_join);
	reset_input(data);
	data->exit_status = 2;
}

void	fd_error(char *file, t_data *data)
{
	ft_putstr_fd("minishell: ", 2);
	perror(file);
	free_all(data);
	exit(1);
}

void	cmd_pathname_error(char *cmd, t_data *data)
{
	char	*message;

	message = ft_strjoin(cmd, ": command not found");
	if (!message)
		error_exit(MALLOC, data);
	ft_putendl_fd(message, 2);
	free(message);
	free_all(data);
	exit(127);
}
