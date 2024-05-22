

// int	remove_white_space_tokens(t_list **tokens)
// {
// 	t_list	*current;
// 	t_list	*tmp;

// 	current = *tokens;
// 	while (current)
// 	{
// 		if (((t_token *)current->content)->type == TOKEN_WHITE_SPACE)
// 		{
// 			tmp = current;
// 			current = current->next;
// 			list_remove(tokens, tmp);
// 		}
// 		else
// 			current = current->next;
// 	}
// 	return (0);
// }
