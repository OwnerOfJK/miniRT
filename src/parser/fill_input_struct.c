/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_input_struct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:24:47 by jkaller           #+#    #+#             */
/*   Updated: 2024/07/30 18:27:10 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

t_object	*parse_objects(char	**object_configs)
{
	t_object	*objects_head;
	t_object	*new_object;
	char		**found_index;

	objects_head = NULL;
	found_index = NULL;
	if (object_configs == NULL)
		return (NULL);
	while ((found_index = find_index(object_configs, "sp", 2)) != NULL
			|| (found_index = find_index(object_configs, "pl", 2)) != NULL
			|| (found_index = find_index(object_configs, "cy", 2)) != NULL)
	{
		new_object = ft_lstnew_object(*found_index);
		ft_lstadd_back_miniRT(&objects_head, new_object);
		object_configs = found_index + 1;
	}
	return (objects_head);
}

t_alight	*parse_alight(char **object_configs)
{
	t_alight		*alight;
	char			*token;
	char			*tmp;
	char			*save_pointer;

	if (object_configs == NULL)
		return (NULL);
	alight = malloc(sizeof(t_alight));
	if (alight == NULL)
		error_message("Error: Memory allocation failed.\n");
	tmp = ft_strdup(*object_configs);
	token = ft_strtok_r(tmp, " ", &save_pointer);
	token = ft_strtok_r(NULL, " ", &save_pointer);
	if (token != NULL)
		alight->ratio = ft_atod(token);
	token = ft_strtok_r(NULL, " ", &save_pointer);
	if (token != NULL)
		alight->color = parse_color(token);
	free(tmp);
	return (alight);
}

t_camera	*parse_camera(char **object_configs)
{
	t_camera	*camera;
	char		*token;
	char		*tmp;
	char		*save_pointer;

	if (object_configs == NULL)
		return (NULL);
	camera = malloc(sizeof(t_camera));
	if (camera == NULL)
		error_message("Error: Memory allocation failed.\n");
	tmp = ft_strdup(*object_configs);
	token = ft_strtok_r(tmp, " ", &save_pointer);
	token = ft_strtok_r(NULL, " ", &save_pointer);
	if (token != NULL)
		camera->pos = parse_coordinate(token);
	token = ft_strtok_r(NULL, " ", &save_pointer);
	if (token != NULL)
		camera->orientation_vector = parse_vector(token);
	token = ft_strtok_r(NULL, " ", &save_pointer);
	camera->fov = ft_atod(token);
	free(tmp);
	return (camera);
}

t_light	*parse_light(char **object_configs)
{
	t_light			*light;
	char			*token;
	char			*tmp;
	char			*save_pointer;

	if (object_configs == NULL)
		return (NULL);
	light = malloc(sizeof(t_light));
	if (light == NULL)
		error_message("Error: Memory allocation failed.\n");
	tmp = ft_strdup(*object_configs);
	token = ft_strtok_r(tmp, " ", &save_pointer);
	token = ft_strtok_r(NULL, " ", &save_pointer);
	if (token != NULL)
		light->pos = parse_coordinate(token);
	token = ft_strtok_r(NULL, " ", &save_pointer);
	if (token != NULL)
		light->brightness = ft_atod(token);
	free(tmp);
	return (light);
}
