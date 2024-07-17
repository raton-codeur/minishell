/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:53:54 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/17 16:41:22 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	env_print_kv(void *p)
{
	t_kv	*kv;

	kv = p;
	if (kv->value)
		printf("%s=%s\n", kv->key, kv->value);
}

void	env_(t_data *data)
{
	list_print(data->env, env_print_kv);
	finish_builtin(0, 0, data);
}
