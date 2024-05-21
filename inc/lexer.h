/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:07:40 by qhauuy            #+#    #+#             */
/*   Updated: 2024/05/21 16:22:09 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

typedef enum e_char_type_1
{
	C_WORD,
	C_PIPE,
	C_SIMPLE_CHEVRON_LEFT,
	C_SIMPLE_CHEVRON_RIGHT,
	C_WHITE_SPACE,
	C_END_OF_STRING,
	C_ERROR,
}	t_char_type_1;

typedef enum e_token_type_1
{
	T_WORD,
	T_PIPE,
	T_SIMPLE_CHEVRON_LEFT,
	T_SIMPLE_CHEVRON_RIGHT
}	t_token_type_1;

typedef struct s_token
{
	char	*content;
	int		type;
}	t_token;

/* lexer.c */
void	print_token(void *p);
int		get_char_type(char c);
t_list	*get_tokens(char *input);








// T_SIMPLE_QUOTE_LEFT,
// T_SIMPLE_QUOTE_RIGHT,
// T_DOUBLE_QUOTE_LEFT,
// T_DOUBLE_QUOTE_RIGHT,

// typedef enum e_token_type_2
// {
// 	T_COMMAND,
// 	T_FILE,
// 	T_PIPE,
// 	T_DELIMITER,
// 	T_SIMPLE_CHEVRON_LEFT,
// 	T_SIMPLE_CHEVRON_RIGHT,
// 	T_DOUBLE_CHEVRON_LEFT,
// 	T_DOUBLE_CHEVRON_RIGHT
// }	t_token_type;

// typedef enum e_state
// {
// 	S_GENERAL_FINISHED,
// 	S_GENERAL_UNFINISHED,
// 	S_,
// }	t_state;

#endif