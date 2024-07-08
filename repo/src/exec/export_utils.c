/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:13:54 by jteste            #+#    #+#             */
/*   Updated: 2024/07/08 17:30:02 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	print_export_content(void *p)
{
	t_kv	*kv;

	kv = p;
	if (kv->value && kv->value[0] != '\0')
		printf("declare -x %s=\"%s\"\n", kv->key, kv->value);
	else
		printf("declare -x %s\n", kv->key);
}

// void	print_export_content(void *p)
// {
// 	t_kv	*kv;
// 	char	*buff;
// 	char	*join;

// 	kv = p;
// 	buff = ft_strjoin("declare -x ", kv->key);
// 	if (buff == NULL)
// 		return ;
// 	join = ft_strjoin(buff, "=\"");
// 	if (join == NULL)
// 	{
// 		free(buff);
// 		return ;
// 	}
// 	free(buff);
// 	buff = ft_strjoin(join, kv->value);
// 	if (buff == NULL)
// 	{
// 		free(join);
// 		return ;
// 	}
// 	free(join);
// 	printf("%s\"\n", buff);
// 	free(buff);
// }
