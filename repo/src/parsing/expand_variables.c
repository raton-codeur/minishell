/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 15:26:17 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/11 13:46:00 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "execution.h"

// static void	set_to_type(t_list *start, t_list *end, int type)
// {
// 	int	target;
// 	while (start != end)
// 	{
// 		target = ((t_token *)start->content)->type;
// 		target = type;
// 		start = start->next;
// 	}
// }

// static void	set_to_variable(t_iterable *current, t_iterable *next)
// {
// 	t_list	*tmp;

// 	tmp = NULL;
// 	while (current->node)
// 	{
// 		if (current->type == T_DOLLAR)
// 		{
// 			if (current->node->next && is_valid_start_variable((char)(((t_token *)(current->node->next->content))->content)[0]))
// 			{
// 				set_iterable(current, current->node->next);
// 				tmp = current->node;
// 				while(is_valid_variable(current->content[0]))
// 					set_iterables(current, next, next->node);
// 				set_to_type(tmp, current->node, T_VARIABLE);
// 			}
// 			else if (current->node->next && next->content[0] == '?')
// 			{
// 				set_iterables(current, next, next->node);
// 				((t_token *)(current->node->content))->type = T_VARIABLE;
// 			}
// 			else
// 				((t_token *)(current->node->content))->type = T_CHARACTER;
// 		}
// 		set_iterables(current, next, next->node);
// 	}
// }


//remplacer le content par itoa du exit status + avancer
	/*free ancien content
	content = itoa
	si cest null
		error exit malloc
	avancer
*/


/* avancer en mettant les type a variable */
	/*tqnt que le type cest char et que le content est un word content*/
		/*type = variable*/
		/*avancer*/
	/*mettre un white space*/

// void	find_variables(t_data *data)
// {
// 	t_iterable	current;
// 	t_iterable	next;

// 	set_iterables(&current, &next, data->tokens);
// 	while (current.node)
// 	{
// 		if (current.type == T_DOLLAR)
// 		{
// 			remove_and_update(&current, &next, data);
// 			if (is_type_content(current, T_CHARACTER, "?"))
// 			{
// 				free(current.content);
// 				current.token->content = ft_itoa(data->exit_status);
// 				if (current.token->content == NULL)
// 					error_exit(MALLOC, data);
// 				current.token->type = T_CHARACTER;
// 			}
// 		}
// 			/*remove and update */
// 			/* si le courant est ?
// 				remplacer le content par itoa du exit status + avancer */
// 			/*sinon si cest un char + debut de variable correct*/
// 				/* avancer en mettant les type a variable */
// 			/* sinon */
// 				/*remove and update*/
// 		else
// 			set_iterables(&current, &next, current.node->next); // on avance
// 	}
// }

// /* on est sur une variable. on veut la remplacer par sa valeur
// si cest une variable normal on veut insert ses white space comme des whitespace et
// a la fin on veut que current soit sur le token dapres
// */
// void	expand_variable(t_iterable *current, t_data *data)
// {
// 	t_iterable	next;

// 	set_iterables(current, &next, current->node);
// 	if (next.content[0] == '?')
// 	{
// 		free(next.content);
// 		next.token->content = ft_itoa(data->exit_status);
// 		if (next.token->content == NULL)
// 			error_exit(MALLOC, data);
// 		next.token->type = T_CHARACTER;
// 	}
// 	else
// 	{
// 		// remplacer char par char par le contenu de la variable

// 	}
// }






static void	find_dollar_chars(t_data *data)
{
	t_iterable	current;
	t_iterable	next;

	set_iterables(&current, &next, data->tokens);
	while (current.node)
	{
		if (current.type == T_DOLLAR
			&& next.type != T_CHARACTER
			&& next.type != T_DOLLAR)
			current.token->type = T_CHARACTER;
		if (current.type == T_DOLLAR && get_quote(next))
			current.token->type = T_CHARACTER;
		set_iterables(&current, &next, current.node->next);
	}
}

static void	set_variable(t_iterable *current)
{
	while (current->node && ft_isword_content(current->content[0]))
	{
		current->token->type = T_VARIABLE;
		set_iterable(current, current->node->next);
	}
}

static void	find_variables(t_data *data)
{
	t_iterable	current;

	set_iterable(&current, data->tokens);
	while (current.node)
	{
		if (current.type == T_DOLLAR)
		{
			current.token->type = T_VARIABLE;
			set_iterable(&current, current.node->next);
			if (ft_isword_start(current.content[0]))
				set_variable(&current);
			else
			{
				current.token->type = T_VARIABLE;
				set_iterable(&current, current.node->next);
			}
		}
		else
			set_iterable(&current, current.node->next);
	}
}

static void	merge_variables(t_data *data)
{
	t_iterable	current;
	t_iterable	next;
	char		*new_content;

	set_iterables(&current, &next, data->tokens);
	while (current.node)
	{
		if (current.type == T_VARIABLE)
		{
			remove_and_update(&current, &next, data);
			while (next.type == T_VARIABLE && next.content[0] != '$')
			{
				new_content = ft_strjoin(current.content,
			}
		}
		set_iterable(&current, current.node->next);
	}
}

static void	expand_variable(t_iterable *current, t_data *data)
{
	char	*new_content;

	if (current->content[0] == '?')
	{
		new_content = ft_itoa(data->exit_status);
		if (new_content == NULL)
			error_exit(MALLOC, data);
		set_token(*current, new_content, T_CHARACTER);
	}
	else if (!in_env(current->content, data))
	{
		new_content = ft_strdup("");
		if (new_content == NULL)
			error_exit(MALLOC, data);
		set_token(*current, new_content, T_CHARACTER);
	}
	else
	{
		new_content = ft_strdup(get_value(in_env(current->content, data)));
		if (new_content == NULL)
			error_exit(MALLOC, data);
		set_token(*current, new_content, T_CHARACTER);
	}
	set_iterable(current, current->node->next);
}

void	expand_variables(t_data *data)
{

	find_dollar_chars(data);
	find_variables(data);
	merge_variable(data);

	list_print(data->tokens, print_token);

	// t_iterable	current;

	// set_iterable(&current, data->tokens);
	// while (current.node)
	// {
	// 	if (current.type == T_VARIABLE)
	// 		expand_variable(&current, data);
	// 	else
	// 		set_iterable(&current, current.node->next);
	// }
}
