/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_utils_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:36:47 by jkaller           #+#    #+#             */
/*   Updated: 2024/07/31 18:54:28 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

t_object	*add_sphere(t_object *object, char *save_pointer)
{
	char		*token;

	object = malloc(sizeof(t_object));
	if (object == NULL)
		error_message("Error: Memory allocation failed.\n");
	object->type = SPHERE;
	token = ft_strtok_r(NULL, " ", &save_pointer);
	if (token != NULL)
		object->pos = parse_coordinate(token);
	token = ft_strtok_r(NULL, " ", &save_pointer);
	if (token != NULL)
		object->shape.sphere.diameter = ft_atod(token);
	token = ft_strtok_r(NULL, " ", &save_pointer);
	if (token != NULL)
		object->color = parse_color(token);
	object->transformation_matrix = m_translate(object->pos);
	object->inverse_matrix = m_inverse(object->transformation_matrix);
	return (object);
}

t_object	*add_plane(t_object *object, char *save_pointer)
{
	char		*token;

	object = malloc(sizeof(t_object));
	if (object == NULL)
		error_message("Error: Memory allocation failed.\n");
	object->type = PLANE;
	token = ft_strtok_r(NULL, " ", &save_pointer);
	if (token != NULL)
		object->pos = parse_coordinate(token);
	token = ft_strtok_r(NULL, " ", &save_pointer);
	if (token != NULL)
		object->shape.plane.normal_vector = parse_vector(token);
	token = ft_strtok_r(NULL, " ", &save_pointer);
	if (token != NULL)
		object->color = parse_color(token);
	object->transformation_matrix = m_translate(object->pos);
	object->inverse_matrix = m_inverse(object->transformation_matrix);
	return (object);
}

void	compute_cylinder_m(t_object *object)
{
	t_vector	y_axis;
	t_vector	rotation_axis;
	double		**rotation_matrix;
	double		**translation_matrix;
	double		rotation_angle;

	y_axis = v_init(0, 1, 0, 0);
	rotation_axis = v_cross(y_axis, object->shape.cylinder.axis_vector);
	rotation_angle = acos(v_dot(y_axis, object->shape.cylinder.axis_vector));
	rotation_matrix = m_rotation(rotation_axis, rotation_angle);
	translation_matrix = m_translate(object->pos);
	object->transformation_matrix = m_mult(translation_matrix, rotation_matrix);
	object->inverse_matrix = m_inverse(object->transformation_matrix);
	free_matrix(rotation_matrix);
	free_matrix(translation_matrix);
}

t_object	*add_cylinder(t_object *object, char *save_pointer)
{
	char	*token;

	object = malloc(sizeof(t_object));
	if (object == NULL)
		error_message("Error: Memory allocation failed.\n");
	object->type = CYLINDER;
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
	compute_cylinder_m(object);
	return (object);
}
