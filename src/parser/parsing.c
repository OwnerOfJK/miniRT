/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 22:14:18 by jkaller           #+#    #+#             */
/*   Updated: 2024/05/22 00:38:00 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	parse_input(char *file_path)
{
	char	**object_configs;

	object_configs = NULL;
	object_configs = check_config(file_path);
	print_double_pointer(object_configs); // This function will be deleted
	free_double_pointer(object_configs); // This function will be deleted
}
