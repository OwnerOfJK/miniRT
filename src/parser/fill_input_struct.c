/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_input_struct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:24:47 by jkaller           #+#    #+#             */
/*   Updated: 2024/08/05 19:37:21 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

t_object	*parse_objects(t_data *data)
{
	t_object	*objects_head;
	t_object	*new_object;
	char		**current_config;

	objects_head = NULL;
	current_config = data->object_configs;
	while (*current_config != NULL)
	{
		if (ft_strncmp(*current_config, "sp", 2) == 0
			|| ft_strncmp(*current_config, "pl", 2) == 0
			|| ft_strncmp(*current_config, "cy", 2) == 0)
		{
			new_object = ft_lstnew_object(data, *current_config, objects_head);
			ft_lstadd_back_minirt(&objects_head, new_object);
		}
		current_config++;
	}
	return (objects_head);
}

t_alight	*parse_alight(t_data *data, char **object_configs)
{
	t_alight		*alight;
	char			*token;
	char			*tmp;
	char			*save_pointer;

	if (object_configs == NULL)
		return (NULL);
	alight = malloc(sizeof(t_alight));
	if (alight == NULL)
		error_free_data(data, "Error: Memory allocation failed.\n");
	tmp = ft_strdup(*object_configs);
	token = ft_strtok_r(tmp, " ", &save_pointer);
	if (check_nb_arg(save_pointer, 2))
	{
		free(alight);
		free(tmp);
		error_free_data(data,
			"Error: Invalid number of arguments of ambient light.\n");
	}
	parse_alight_attributes(alight, save_pointer);
	free(tmp);
	return (alight);
}

void	parse_alight_attributes(t_alight *alight, char *save_pointer)
{
	char	*token;

	token = ft_strtok_r(NULL, " ", &save_pointer);
	if (token != NULL)
		alight->ratio = ft_atod(token);
	token = ft_strtok_r(NULL, " ", &save_pointer);
	if (token != NULL)
		alight->color = parse_color(token);
}

t_camera	*parse_camera(t_data *data, char **object_configs)
{
	t_camera	*camera;
	char		*token;
	char		*tmp;
	char		*save_pointer;

	if (object_configs == NULL)
		return (NULL);
	camera = malloc(sizeof(t_camera));
	if (camera == NULL)
		error_free_data(data, "Error: Memory allocation failed.\n");
	tmp = ft_strdup(*object_configs);
	token = ft_strtok_r(tmp, " ", &save_pointer);
	if (check_nb_arg(save_pointer, 3))
	{
		free(camera);
		free(tmp);
		error_free_data(data, "Error: Invalid number of arguments of camera.\n");
	}
	parse_cam_attributes(camera, save_pointer);
	free(tmp);
	return (camera);
}

t_light	*parse_light(t_data *data, char **object_configs)
{
	t_light			*light;
	char			*token;
	char			*tmp;
	char			*save_pointer;

	if (object_configs == NULL)
		return (NULL);
	light = malloc(sizeof(t_light));
	if (light == NULL)
		error_free_data(data, "Error: Memory allocation failed.\n");
	tmp = ft_strdup(*object_configs);
	token = ft_strtok_r(tmp, " ", &save_pointer);
	if (check_nb_arg(save_pointer, 3))
	{
		free(light);
		free(tmp);
		error_free_data(data, "Error: Invalid number of arguments of light.\n");
	}
	parse_light_attributes(light, save_pointer);
	free(tmp);
	return (light);
}
