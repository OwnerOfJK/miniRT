/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_utils_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 18:53:39 by ecarlier          #+#    #+#             */
/*   Updated: 2024/08/05 19:34:30 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

void	parse_plane_attributes(t_object *object, char *save_pointer)
{
	char	*token;

	token = ft_strtok_r(NULL, " ", &save_pointer);
	if (token != NULL)
		object->pos = parse_coordinate(token);
	token = ft_strtok_r(NULL, " ", &save_pointer);
	if (token != NULL)
		object->shape.plane.normal_vector = parse_vector(token);
	token = ft_strtok_r(NULL, " ", &save_pointer);
	if (token != NULL)
		object->color = parse_color(token);
	token = ft_strtok_r(NULL, " ", &save_pointer);
}

void	parse_cylinder_attributes(t_object *object, char *save_pointer)
{
	char	*token;

	token = ft_strtok_r(NULL, " ", &save_pointer);
	if (token != NULL)
		object->pos = parse_coordinate(token);
	token = ft_strtok_r(NULL, " ", &save_pointer);
	if (token != NULL)
		object->shape.cylinder.axis_vector = v_normalize(parse_vector(token));
	token = ft_strtok_r(NULL, " ", &save_pointer);
	if (token != NULL)
		object->shape.cylinder.diameter = ft_atod(token);
	token = ft_strtok_r(NULL, " ", &save_pointer);
	if (token != NULL)
		object->shape.cylinder.height = ft_atod(token);
	token = ft_strtok_r(NULL, " ", &save_pointer);
	if (token != NULL)
		object->color = parse_color(token);
}

void	parse_sphere_attributes(t_object *object, char *save_pointer)
{
	char	*token;

	token = ft_strtok_r(NULL, " ", &save_pointer);
	if (token != NULL)
		object->pos = parse_coordinate(token);
	token = ft_strtok_r(NULL, " ", &save_pointer);
	if (token != NULL)
		object->shape.sphere.diameter = ft_atod(token);
	token = ft_strtok_r(NULL, " ", &save_pointer);
	if (token != NULL)
		object->color = parse_color(token);
}

void	parse_light_attributes(t_light *light, char *save_pointer)
{
	char	*token;

	token = ft_strtok_r(NULL, " ", &save_pointer);
	if (token != NULL)
		light->pos = parse_coordinate(token);
	token = ft_strtok_r(NULL, " ", &save_pointer);
	if (token != NULL)
		light->brightness = ft_atod(token);
}

void	parse_cam_attributes(t_camera *camera, char *save_pointer)
{
	char	*token;

	token = ft_strtok_r(NULL, " ", &save_pointer);
	if (token != NULL)
		camera->pos = parse_coordinate(token);
	token = ft_strtok_r(NULL, " ", &save_pointer);
	if (token != NULL)
		camera->orientation_vector = parse_vector(token);
	token = ft_strtok_r(NULL, " ", &save_pointer);
	camera->fov = ft_atod(token);
}
