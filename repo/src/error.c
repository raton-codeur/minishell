/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteste <jteste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 16:26:24 by qhauuy            #+#    #+#             */
/*   Updated: 2024/06/25 13:34:26 by jteste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(int code)
{
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

	message = ft_strjoin("syntax error near unexpected token `", token);
	if (!message)
		error_exit(MALLOC, data);
	message_join = ft_strjoin(message, "'");
	mmm_free(message);
	if (!message_join)
		error_exit(MALLOC, data);
	ft_putendl_fd(message_join, 2);
	mmm_free(message_join);
	reset_input(data);
	/* mettre le code d'erreur de $? à 2 */
}

void	fd_error(char *file)
{
	ft_putstr_fd("minishell: ", 2);
	perror(file);
	mmm_free_all();
	exit(1);
}

void	cmd_name_error(char *cmd, t_data *data)
{
	char	*message;

	message = ft_strjoin(cmd, ": command not found");
	if (!message)
		error_exit(MALLOC, data);
	ft_putendl_fd(message, 2);
	mmm_free(message);
	mmm_free_all();
	exit(1);
	/* mettre le code d'erreur de $? à 127 */
}
