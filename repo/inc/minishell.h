/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:37:50 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/01 19:03:33 by qhauuy           ###   ########.fr       */
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
/* wait, waitpid, wait3, wait4, kill */
# include <sys/stat.h>
/* stat, lstat, fstat */
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
	T_DELIMITER
};

typedef struct s_token
{
	int		type;
	char	*content;
	int		here_doc;
}	t_token;

typedef struct s_iterable
{
	t_list	*node;
	t_token	*token;
	char	*content;
	int		type;
	int		here_doc;
}	t_iterable;

typedef struct s_tree
{
	void			*content;
	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;

typedef struct s_cmd
{
	char	*pathname;
	int		argc;
	char	**argv;
}	t_cmd;

enum e_error
{
	MALLOC,
	READLINE,
	LEXING,
	QUOTE,
	PIPE,
	FORK,
	ENV
};

typedef struct envp
{
	char	*key;
	char	*value;
}t_envp;


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
	t_list		*envp;
	int			exit_status;
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
void	free_env(void *p);

/* free.c */
void	free_input(t_data *data);
void	free_all(t_data *data);
void	reset_input(t_data *data);
void	close_2(int pipe_[2]);

/* error.c */
void	print_error(int code);
void	error(int code, t_data *data);
void	error_exit(int code, t_data *data);
void	syntax_error(char *token, t_data *data);
void	fd_error(char *file, t_data *data);
void	cmd_pathname_error(char *cmd, t_data *data);

/* init_data.c */
void	init_data(t_data *data, int argc, char **argv, char **envp);
void	get_path(t_data *data);
void	get_input(t_data *data);

#endif
