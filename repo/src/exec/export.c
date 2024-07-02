/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:00:46 by jteste            #+#    #+#             */
/*   Updated: 2024/07/02 16:24:10 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	sort_export_list(t_list **envp)
{
	t_list	*current;
	t_list	*next;
	t_envp	*tmp;

	current = *envp;
	while (current)
	{
		next = current->next;
		while (next)
		{
			if (ft_strcmp(((t_envp *)current->content)->key,
					((t_envp *)next->content)->key) > 0)
			{
				tmp = current->content;
				current->content = next->content;
				next->content = tmp;
			}
			next = next->next;
		}
		current = current->next;
	}
}

void	print_export(t_list **envp)
{
	t_list	*current;
	char	*buff;
	char	*join;

	current = *envp;
	sort_export_list(&current);
	while (current)
	{
		buff = ft_strjoin("declare -x ", ((t_envp *)current->content)->key);
		join = ft_strjoin(buff, "=\"");
		free(buff);
		buff = ft_strjoin(join, ((t_envp *)current->content)->value);
		free(join);
		join = ft_strjoin(buff, "\"\n");
		free(buff);
		printf("%s", join);
		free(join);
		current = current->next;
	}
}