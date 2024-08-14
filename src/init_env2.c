/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 16:45:44 by jteste            #+#    #+#             */
/*   Updated: 2024/08/13 15:05:20 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_path(t_data *data)
{
	t_list	*node;
	char	*new_value;

	node = in_env("PATH", data);
	if (node == NULL)
		insert_in_env("PATH=", data);
	new_value = ft_strdup("/usr/bin");
	if (new_value == NULL)
		return (error_exit(MALLOC, data));
	reset_value("PATH", new_value, data);
}
