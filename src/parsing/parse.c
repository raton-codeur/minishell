/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:20:43 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/14 15:06:24 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	parse(t_data *data)
{
	if (data->input == NULL)
		return ;
	init_tokens(data);
	parse_quotes(data);
	get_double_brokets(data);
	find_delimiters(data);
	find_last_dollar_chars(data);
	expand_variables(data);
	get_words(data);
	parse_brokets(data);
}
