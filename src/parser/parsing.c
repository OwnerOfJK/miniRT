/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 22:14:18 by jkaller           #+#    #+#             */
/*   Updated: 2024/08/05 15:33:34 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

bool static	check_rgb(t_input *input)
{
	t_object	*current;
	t_alight	*alight;

	current = input->objects;
	while (current != NULL)
	{
		if (current->color.r < 0 || current->color.r > 255
			|| current->color.g < 0 || current->color.g > 255
			|| current->color.b < 0 || current->color.b > 255)
			return (true);
		current = current->next;
	}
	alight = input->alight;
	if (alight->color.r < 0 || alight->color.r > 255
		|| alight->color.g < 0 || alight->color.g > 255
		|| alight->color.b < 0 || alight->color.b > 255)
		return (true);
	return (false);
}

bool static	check_ambient_light(t_input *input)
{
	t_alight	*alight;

	alight = input->alight;
	if (alight->ratio < 0 || alight->ratio > 1)
		return (true);
	else
		return (false);
}

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
	if (check_rgb(input))
		error_free_data(data, "Error: R,G,B colors not in range [0-255].\n");
	if (check_ambient_light(input))
		error_free_data(data, "Error: ambient lighting ratio not in range [0.0,1.0] \n");
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
