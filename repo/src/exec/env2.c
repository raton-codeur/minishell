/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 15:27:39 by jteste            #+#    #+#             */
/*   Updated: 2024/07/06 13:25:12 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

// t_list	*find_env_key(t_list **envp, char *key_to_find)
// {
// 	t_list	*current;

// 	current = *envp;
// 	while (current)
// 	{
// 		if (ft_strcmp(((t_envp *)current->content)->key, key_to_find) == 0)
// 			return (current);
// 		current = current->next;
// 	}
// 	return (NULL);
// }

// void	modify_key_value(t_list **envp, char *key_to_find, char *new_value)
// {
// 	t_list	*target;

// 	target = find_env_key(envp, key_to_find);
// 	if (target)
// 	{
// 		free(((t_envp *)target->content)->value);
// 		((t_envp *)target->content)->value = ft_strdup(new_value);
// 	}
// }
