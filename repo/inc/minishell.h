/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:37:50 by qhauuy            #+#    #+#             */
/*   Updated: 2024/06/20 16:45:07 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
/* readline, rl_clear_history, rl_on_new_line
       rl_replace_line, rl_redisplay, add_history */
# include <stdio.h>
/* printf, perror */
# include <stdlib.h>
/* malloc, free, exit, getenv */
# include <unistd.h>
/* write, access, open, read, close, fork
       getcwd, chdir, unlink, execve, dup, dup2
       pipe, isatty, ttyname, ttyslot */
# include <sys/types.h>
/* wait, waitpid, wait3, wait4, stat, lstat
       fstat, kill */
# include <sys/wait.h>
/* wait, waitpid, wait3, wait4 */
# include <signal.h>
/* signal, sigaction, sigemptyset, sigaddset */
# include <dirent.h>
/* opendir, readdir, closedir */
# include <string.h>
/* strerror */
# include <sys/ioctl.h>
/* ioctl */
# include <termios.h>
/* tcsetattr, tcgetattr */
# include <curses.h>
/* tgetent, tgetflag, tgetnum, tgetstr
       tgoto, tputs */

# include "libft.h"

enum e_token
{
	T_PIPE,
	T_BROKET_LEFT,
	T_BROKET_RIGHT,
	T_DOUBLE_BROKET_LEFT,
	T_DOUBLE_BROKET_RIGHT,
	T_SIMPLE_QUOTE,
	T_DOUBLE_QUOTE,
	T_DOLLAR,
	T_WHITE_SPACE,
	T_CHARACTER,
	T_WORD,
	T_VARIABLE,
	T_DELIMITER,
	T_ERROR,
};

typedef struct s_token
{
	int		type;
	char	*content;
	int		read_write[2];
}	t_token;

typedef struct s_iterable
{
	t_list	*node;
	t_token	*token;
	char	*content;
	int		type;
}	t_iterable;

typedef struct s_tree
{
	void			*content;
	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;

enum e_error
{
	MALLOC,
	READ_LINE,
	QUOTE,
	FORK,
	DUP,
	EXEC,
	IN,
	OUT,
	PIPE
};

typedef struct s_cmd
{
	char	*pathname;
	char	**argv;
}	t_cmd;

typedef struct s_pipe
{
	int		in;
	int		out;
	int		read_write[2];
	t_cmd	*cmd[2];
}	t_pipe;

typedef struct s_data
{
	char		*input;
	t_list		*tokens;
	t_tree		*ast;
	t_tree		*tree;
	char		**path;
	int			in;
	int			out;
	t_cmd		*cmd;
}	t_data;

/* print.c */
// a supp
void	print_type(int type);
void	print_token(void *p);
void	tree_print(t_tree *tree);
void	print_cmd(t_cmd *cmd);

/* free_utils.c */
void	free_token(void *p);
void	tree_clear(t_tree **tree);
void	free_cmd(t_data *data);

/* free.c */
void	free_input(t_data *data);
void	free_all(t_data *data);
void	reset_input(t_data *data);

/* error.c */
void	print_error(int code);
void	error(int code, t_data *data);
void	error_exit(int code, t_data *data);
void	syntax_error(char *token, t_data *data);
void	fd_error(char *file, t_data *data);

/* init_data.c */
void	init_data(t_data *data);
void	get_path(t_data *data);

#endif
