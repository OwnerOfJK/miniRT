/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 22:14:18 by jkaller           #+#    #+#             */
/*   Updated: 2024/06/16 16:01:01 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

t_input	*configs_to_struct(char	**object_configs)
{
	t_input	*input;

	input = malloc(sizeof(t_data));
	if (input == NULL)
		error_message("Error: Memory allocation failed.\n");
	input->ambient = parse_alightning(find_index(object_configs, "A", 1));
	input->camera = parse_camera(find_index(object_configs, "C", 1));
	input->light = parse_light(find_index(object_configs, "L", 1));
	input->sphere = parse_sphere(find_index(object_configs, "sp", 2));
	input->plane = parse_plane(find_index(object_configs, "pl", 2));
	input->cylinder = parse_cylinder(find_index(object_configs, "cy", 2));
	return (input);
}

t_data	*parse_input(char *file_path)
{
	char	**object_configs;
	t_data	*input;

	object_configs = NULL;
	object_configs = check_config(file_path);
	input = configs_to_struct(object_configs);
	//print_data(input); // This function will be deleted
	free_double_pointer(object_configs); // This function will be deleted
	return (input);
}

