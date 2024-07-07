/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:15:43 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/07 16:42:54 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

void	print_type(int type)
{
	if (type == T_PIPE)
		printf("type : PIPE\n");
	else if (type == T_BROKET_LEFT)
		printf("type : BROKET_LEFT\n");
	else if (type == T_BROKET_RIGHT)
		printf("type : BROKET_RIGHT\n");
	else if (type == T_DOUBLE_BROKET_LEFT)
		printf("type : DOUBLE_BROKET_LEFT\n");
	else if (type == T_DOUBLE_BROKET_RIGHT)
		printf("type : DOUBLE_BROKET_RIGHT\n");
	else if (type == T_SIMPLE_QUOTE)
		printf("type : SIMPLE_QUOTE\n");
	else if (type == T_DOUBLE_QUOTE)
		printf("type : DOUBLE_QUOTE\n");
	else if (type == T_DOLLAR)
		printf("type : DOLLAR\n");
	else if (type == T_WHITE_SPACE)
		printf("type : WHITE_SPACE\n");
	else if (type == T_CHARACTER)
		printf("type : CHARACTER\n");
	else if (type == T_WORD)
		printf("type : WORD\n");
	else if (type == T_VARIABLE)
		printf("type : VARIABLE\n");
	else if (type == T_DELIMITER)
		printf("type : DELIMITER\n");
}

void	print_token(void *p)
{
	t_token	*token;

	token = p;
	printf("content : <%s>\n", token->content);
	print_type(token->type);
}

static void	print_token_line(void *content)
{
	t_token	*token;

	token = content;
	if (token->type == T_PIPE)
		printf("\033[97;41m");
	else if (token->type == T_BROKET_LEFT
		|| token->type == T_BROKET_RIGHT
		|| token->type == T_DOUBLE_BROKET_RIGHT)
		printf("\033[97;45m");
	else if (token->type == T_DOUBLE_BROKET_LEFT)
		printf("\033[97;44m");
	else if (token->type == T_WORD)
		printf("\033[97;40m");
	printf(" %s ", token->content);
}

static void	tree_print_rec(t_tree *tree, int *tab_count)
{
	int	i;

	if (tree == NULL)
		return ;
	(*tab_count)++;
	tree_print_rec(tree->right, tab_count);
	(*tab_count)--;
	i = 0;
	while (i < *tab_count)
	{
		printf("\t");
		i++;
	}
	list_print(tree->content, print_token_line);
	printf("\033[0m");
	printf("\n");
	(*tab_count)++;
	tree_print_rec(tree->left, tab_count);
	(*tab_count)--;
}

void	tree_print(t_tree *tree)
{
	int	tab_count;

	tab_count = 0;
	if (tree == NULL || list_size(tree->content) == 0)
		return ;
	tree_print_rec(tree, &tab_count);
}

void	print_cmd(t_cmd *cmd)
{
	int	i;

	printf("pathname : <%s>\n", cmd->pathname);
	printf("argv :\n");
	i = 0;
	while (cmd->argv[i])
		printf("<%s>\n", cmd->argv[i++]);
}

void	print_kv(void *p)
{
	t_kv	*kv;

	kv = p;
	printf("%s=%s\n", kv->key, kv->value);
}
