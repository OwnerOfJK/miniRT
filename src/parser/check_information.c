/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_information.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 23:01:11 by jkaller           #+#    #+#             */
/*   Updated: 2024/05/27 20:46:21 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	check_for_unique_elements(char **object_configs)
{
	int	i;
	int	variable_count;

	i = 0;
	variable_count = 0;
	while (object_configs[i])
	{
		if (object_configs[i][0] == 'A'
			|| object_configs[i][0] == 'C' || object_configs[i][0] == 'L')
			variable_count++;
		i++;
	}
	if (variable_count != 3)
		error_message("Error: Missing or too many A, C or L elements.\n");
}

void	check_information(char **object_configs)
{
	check_for_unique_elements(object_configs); // this should check for A, C, L to be unique, but thinking if I should parse this to a 
	//check resolution
	//check ambient light
	//check camera
	//check light
	//check sphere
	//check plane
	//check square
	//check cylinder
	//check triangle
	return ;
}
