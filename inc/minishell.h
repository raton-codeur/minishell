/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:37:50 by qhauuy            #+#    #+#             */
/*   Updated: 2024/06/13 10:26:43 by qhauuy           ###   ########.fr       */
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

# define MALLOC_MSG "malloc error"
# define MALLOC 426

typedef struct s_token
{
	char	*content;
	int		type;
}	t_token;

enum
{
	T_PIPE,
	T_BROKET_LEFT,
	T_BROKET_RIGHT,
	T_SIMPLE_QUOTE,
	T_DOUBLE_QUOTE,
	T_DOLLAR,
	T_WHITE_SPACE,
	T_CHARACTER,
	T_ERROR,
	T_VARIABLE,
	T_WORD,
	T_COMMAND,
	T_FILE,
	T_DELIMITER,
	T_DOUBLE_BROKET_LEFT,
	T_DOUBLE_BROKET_RIGHT,
};

typedef struct s_iterable
{
	t_list	*node;
	t_token	*token;
	char	*content;
	int		type;
}	t_iterable;

typedef struct s_tree	t_tree;
struct s_tree
{
	void	*content;
	t_tree	*left;
	t_tree	*right;
};

typedef struct s_data
{
	t_list		*to_free;
	char		*input;
	t_list		*tokens;
	t_tree		*ast;
}	t_data;

/* print.c */
// a supp
void	print_type(int type);
void	print_token(void *p);
void	tree_print(t_tree *tree);
void	print_token_line(void *content);

/* utils_1.c */
void	*save(void *p, t_data *data);
void	free_token(void *p);
void	free_save(void *p, t_data *data);
void	free_all(t_data *data);
void	error_exit(int code, t_data *data);

/* utils_2.c */
void	tree_clear(t_tree *tree);

#endif