/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteste <jteste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:53:54 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/17 16:02:17 by jteste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

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
	finish_builtin(0, 0, data);
}
