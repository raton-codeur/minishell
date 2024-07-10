/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 15:26:17 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/10 17:37:32 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "execution.h"

/*
 a $ b c d whitespace -> a bcd whitespace
 a $ 0 c whitespace -> a c whitespace
 a $ % c whitespace -> a c whitespace
 a $ ? c whitespace -> a ? whitespace
 a $ whitespace -> a $ whitespace (type devient char)
*/

static int	is_valid_start_variable(char c)
{
	return(ft_isalpha(c) || c == '_');
}

static int	is_valid_variable(char c)
{
	return(ft_isalnum(c) || c == '_');
}

static void	set_to_type(t_list *start, t_list *end, int type)
{
	int	target;
	while (start != end)
	{
		target = ((t_token *)start->content)->type;
		target = type;
		start = start->next;
	}
}
static void	set_to_variable(t_iterable *current, t_iterable *next)
{
	t_list	*tmp;

	tmp = NULL;
	while (current->node)
	{
		if (current->type == T_DOLLAR)
		{
			if (current->node->next && is_valid_start_variable((char)(((t_token *)(current->node->next->content))->content)[0]))
			{
				set_iterable(current, current->node->next);
				tmp = current->node;
				while(is_valid_variable(current->content[0]))
					set_iterables(current, next, next->node);
				set_to_type(tmp, current->node, T_VARIABLE);
			}
			else if (current->node->next && next->content[0] == '?')
			{
				set_iterables(current, next, next->node);
				((t_token *)(current->node->content))->type = T_VARIABLE;
			}
			else
				((t_token *)(current->node->content))->type = T_CHARACTER;
		}
		set_iterables(current, next, next->node);
	}
}

void	find_variables(t_data *data)
{
	t_iterable	current;
	t_iterable	next;

	set_iterables(&current, &next, data->tokens);
	while (current.node)
	{
		if (current.type == T_DOLLAR)
		{

		}
		else
			set_iterables(&current, &next, current.node->next);
	}
}

/* on est sur une variable. on veut la remplacer par sa valeur
si cest une variable normal on veut insert ses white space comme des whitespace et 
a la fin on veut que current soit sur le token dapres
*/
void	expand_variable(t_iterable *current, t_data *data)
{
	t_iterable	next;

	set_iterables(current, &next, current.node);
	if (next.content[0] == '?')
	{
		free(next.content);
		next.token->content = ft_itoa(data->exit_status);
		if (next.token->content == NULL)
			error_exit(MALLOC, data);
		next.token->type = T_CHARACTER;
	}
	else
	{
		// remplacer char par char par le contenu de la variable

	}
}

void	expand_variables(t_data *data)
{
	t_iterable	current;
	t_iterable	next;

	find_variables(data);
	change_type(data, T_DOLLAR, T_CHARACTER);
	set_iterables(&current, &next, data->tokens);
	// if (current.type == T_VARIABLE)
	// {
	// 	// nouveau debut de tokens = get  tokens ( get value de la varable )
	// 	// set iterable (current, next, tokens)
	// 	// suivant du dernier nouveau token = tokens
	// }
	while (current.node)
	{
		if (next.type == T_VARIABLE)
			expand_variable(&current, data);
		else
			set_iterable(&current, current.node->next);
	}
	change_type(data, T_VARIABLE, T_CHARACTER);
}
