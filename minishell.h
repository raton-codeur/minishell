/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:47:01 by qhauuy            #+#    #+#             */
/*   Updated: 2024/05/21 13:30:06 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
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


/* get_path_list.c */
char	**get_path_list(char *path);


#endif