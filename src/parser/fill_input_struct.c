/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_input_struct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:24:47 by jkaller           #+#    #+#             */
/*   Updated: 2024/05/27 21:35:00 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

t_alightning	*parse_alightning(char **object_configs)
{
	t_alightning	*alightning;
	char			*double_value;

	double_value = find_and_extract_double(*object_configs, 1);
	alightning = malloc(sizeof(t_alightning));
	if (alightning == NULL)
		error_message("Error: Memory allocation failed.\n");
	alightning->ratio = ft_atod(double_value);
	alightning->color = parse_to_color(*object_configs);
	return (alightning);
}
