/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_input_struct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:24:47 by jkaller           #+#    #+#             */
/*   Updated: 2024/05/28 00:01:24 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

t_alightning	*parse_alightning(char **object_configs)
{
	t_alightning	*alightning;
	char			*token;
	char			*tmp;
	char			*save_pointer;

	alightning = malloc(sizeof(t_alightning));
	if (alightning == NULL)
		error_message("Error: Memory allocation failed.\n");
	tmp = ft_strdup(*object_configs);
	token = ft_strtok_r(tmp, " ", &save_pointer);
	token = ft_strtok_r(NULL, " ", &save_pointer);
	if (token != NULL)
		alightning->ratio = ft_atod(token);
	token = ft_strtok_r(NULL, " ", &save_pointer);
	if (token != NULL)
		alightning->color = parse_to_color(token);
	return (alightning);
}

t_camera	*parse_camera(char **object_configs)
{
	t_camera	*camera;
	char		*token;
	char		*tmp;
	char		*save_pointer;

	camera = malloc(sizeof(t_camera));
	if (camera == NULL)
		error_message("Error: Memory allocation failed.\n");
	tmp = ft_strdup(*object_configs);
	token = ft_strtok_r(tmp, " ", &save_pointer);
	token = ft_strtok_r(NULL, " ", &save_pointer);
	if (token != NULL)
		camera->pos = parse_to_pos(token);
	token = ft_strtok_r(NULL, " ", &save_pointer);
	if (token != NULL)
		camera->orientation_vector = parse_to_pos(token);
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

	light = malloc(sizeof(t_light));
	if (light == NULL)
		error_message("Error: Memory allocation failed.\n");
	tmp = ft_strdup(*object_configs);
	token = ft_strtok_r(tmp, " ", &save_pointer);
	token = ft_strtok_r(NULL, " ", &save_pointer);
	if (token != NULL)
		light->pos = parse_to_pos(token);
	token = ft_strtok_r(NULL, " ", &save_pointer);
	if (token != NULL)
		light->brightness = ft_atod(token);
	return (light);
}
