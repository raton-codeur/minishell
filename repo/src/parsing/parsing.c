/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:20:43 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/10 15:31:02 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	parsing(t_data *data)
{
	init_tokens(data);
	parse_quotes(data);
	get_double_brokets(data);
	parse_delimiters(data);
	expand_variables(data);
	remove_quotes(data);
	get_words(data);
	parse_brokets(data);

	list_print(data->tokens, print_token);
}
