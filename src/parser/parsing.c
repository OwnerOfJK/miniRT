/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 22:14:18 by jkaller           #+#    #+#             */
/*   Updated: 2024/08/05 19:04:07 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

t_input	*configs_to_struct(t_data *data)
{
	t_input	*input;

	input = ft_calloc(sizeof(t_input), 1);
	if (input == NULL)
		error_free_data(data, "Error: Memory allocation failed.\n");
	data->input = input;
	input->alight = parse_alight(data,
			find_index(data->object_configs, "A", 1));
	input->camera = parse_camera(data,
			find_index(data->object_configs, "C", 1));
	input->light = parse_light(data, find_index(data->object_configs, "L", 1));
	input->objects = parse_objects(data);
	input->material = material_init(data);
	input->viewport = viewport_init(data, input->camera);
	check_arg(data, input);
	return (input);
}

t_input	*parse_input(t_data *data, char *file_path)
{
	int		config_len;
	t_input	*input;

	config_len = get_config_len(data, file_path);
	check_config(data, file_path, config_len);
	input = configs_to_struct(data);
	return (input);
}
