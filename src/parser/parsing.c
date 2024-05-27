/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 22:14:18 by jkaller           #+#    #+#             */
/*   Updated: 2024/05/28 01:38:25 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

t_input	*configs_to_struct(char	**object_configs)
{
	t_input	*input;

	input = malloc(sizeof(t_input));
	if (input == NULL)
		error_message("Error: Memory allocation failed.\n");
	input->alightning = parse_alightning(find_index(object_configs, "A", 1));
	input->camera = parse_camera(find_index(object_configs, "C", 1));
	input->light = parse_light(find_index(object_configs, "L", 1));
	input->sphere = parse_sphere(find_index(object_configs, "sp", 2));
	input->plane = parse_plane(find_index(object_configs, "pl", 2));
	input->cylinder = parse_cylinder(find_index(object_configs, "cy", 2));
	return (input);
}

t_input	*parse_input(char *file_path)
{
	char	**object_configs;
	t_input	*input;

	object_configs = NULL;
	object_configs = check_config(file_path);
	input = configs_to_struct(object_configs);
	print_input(input); // This function will be deleted
	free_double_pointer(object_configs); // This function will be deleted
	return (input);
}

