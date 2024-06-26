/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteste <jteste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:15:43 by qhauuy            #+#    #+#             */
/*   Updated: 2024/06/26 13:39:05 by jteste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
// Fonctions du dessous a securiser

void	print_envp_export(t_list **envp)
{
	t_list	*current;
	char	*buff;
	char	*join;

	current = *envp;
	while (current)
	{
		buff = ft_strjoin("declare -x ", ((t_envp *)current->content)->key);
		join = ft_strjoin(buff, "=\"");
		mmm_free(buff);
		buff = ft_strjoin(join, ((t_envp *)current->content)->value);
		mmm_free(join);
		join = ft_strjoin(buff, "\"\n");
		mmm_free(buff);
		printf("%s", join);
		mmm_free(join);
		current = current->next;
	}
}
void	print_envp_env(t_list **envp)
{
	t_list	*current;
	char	*buff;
	char	*join;

	current = *envp;
	while (current)
	{
		buff = ft_strjoin(((t_envp *)current->content)->key, "=");
		join = ft_strjoin(buff, ((t_envp *)current->content)->value);
		mmm_free(buff);
		buff = ft_strjoin(join, "\n");
		mmm_free(join);
		printf("%s", buff);
		current = current->next;
	}
}
