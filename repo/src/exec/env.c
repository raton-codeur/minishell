/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:53:54 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/08 17:27:29 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	print_kv_env(void *p)
{
	t_kv	*kv;

	kv = p;
	if (kv->value && kv->value[0] != '\0')
		printf("%s=%s\n", kv->key, kv->value);
}

void	env_(t_data *data)
{
	list_print(data->env, print_kv_env);
	free_all(data);
	exit(0);
}

char	**env_to_double_array(t_data *data)
{
	char	**result;
	char	*tmp;
	t_list	*current;
	int		i;

	current = data->env;
	result = ft_calloc(list_size(data->env) + 1, sizeof(char *));
	if (result == NULL)
		error_exit(MALLOC, data);
	i = 0;
	while (current)
	{
		if (ft_strcmp(get_value(current), "") == 0)
		{
			current = current->next;
			continue ;
		}
		tmp = ft_strjoin(get_key(current), "=");
		if (tmp == NULL)
			return (deep_free((void **)result, i), error_exit(MALLOC, data), NULL);
		result[i] = ft_strjoin(tmp, get_value(current));
		free(tmp);
		if (result[i] == NULL)
			return (deep_free((void **)result, i), error_exit(MALLOC, data), NULL);
		current = current->next;
		i++;
	}
	result[i] = NULL;
	return (result);
}
