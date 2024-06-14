#include "minishell.h"

void set_priority(t_data *data, t_list tokens)
{
	t_iterable	current;

	set_iterable(&current, tokens);
	while (current.node)
	{
		if (current.type == T_PIPE)
			current.node->priority = 1;
		else if (current.type == T_BROKET_LEFT || current.type == T_BROKET_RIGHT || current.type == T_DOUBLE_BROKET_LEFT ||  current.type == T_DOUBLE_BROKET_RIGHT)
			current.node->priority = 2;
		else if (current.type == T_WORD)
			current.node->priority = 3;
		set_iterable(&current, current.node->next);
	}
	
}