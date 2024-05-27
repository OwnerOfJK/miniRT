/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_input_struct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:24:47 by jkaller           #+#    #+#             */
/*   Updated: 2024/05/27 17:55:46 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

t_alightning    *parse_alightning(char **object_configs)
{
	t_alightning    *alightning;
	char			*double_value;

	double_value = find_and_extract_double(*object_configs, 1);
	ft_printf("%s\n", double_value);
	alightning = malloc(sizeof(t_alightning));
	if (alightning == NULL)
		error_message("Error: Memory allocation failed.\n");
	alightning->ratio = ft_atof(double_value);
	//alightning->color = parse_color(object_configs[2]);
	return (alightning);
}
