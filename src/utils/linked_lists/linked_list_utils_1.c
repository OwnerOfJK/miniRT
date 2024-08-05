/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_utils_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 00:23:57 by jkaller           #+#    #+#             */
/*   Updated: 2024/08/05 17:39:58 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

bool	check_nb_arg(t_data *data, char *save_pointer, int nb)
{
	int			arg_count;
	char		*token;
	char		*temp;
	int			i;
	char		*to_free;

	(void)data;
	temp = ft_strdup(save_pointer);
	arg_count = 0;
	i = 0;
	to_free = temp;
	token = ft_strtok_r(NULL, " ", &temp);
	if (token != NULL)
		arg_count++;
	token = ft_strtok_r(NULL, " ", &temp);
	if (token != NULL)
		arg_count++;
	token = ft_strtok_r(NULL, " ", &temp);
	if (token != NULL)
		arg_count++;
	token = ft_strtok_r(NULL, " ", &temp);
	if (token != NULL)
		arg_count++;
	if (nb == 5)
	{
		while (i <= 2)
		{
			token = ft_strtok_r(NULL, " ", &temp);
			if (token != NULL)
				arg_count++;
			i++;
		}
	}
	free(to_free);
	if (arg_count != nb)
		return (true);
	else
		return (false);
}

t_object	*add_sphere(t_data *data, t_object *object, char *save_pointer, char *tmp)
{
	char		*token;

	object = malloc(sizeof(t_object));
	if (object == NULL)
		error_free_data(data, "Error: Memory allocation failed.\n");
	object->type = SPHERE;
	if (check_nb_arg(data, save_pointer, 3))
	{
		free(object);
		free(tmp);
		error_free_data(data, "Error: Invalid number of arguments of a sphere.\n");
	}
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

t_object	*add_plane(t_data *data, t_object *object, char *save_pointer, char *tmp)
{
	char		*token;


	object = malloc(sizeof(t_object));
	if (object == NULL)
		error_free_data(data, "Error: Memory allocation failed.\n");
	object->type = PLANE;
	if (check_nb_arg(data, save_pointer, 3))
	{
		free(object);
		free(tmp);
		error_free_data(data, "Error: Invalid number of arguments of a plane.\n");
	}
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

t_object	*add_cylinder(t_data *data, t_object *object, char *save_pointer, char *tmp)
{
	char		*token;

	object = malloc(sizeof(t_object));
	if (object == NULL)
		error_free_data(data, "Error: Memory allocation failed.\n");
	object->type = CYLINDER;
	if (check_nb_arg(data, save_pointer, 5))
	{
		free(object);
		free(tmp);
		error_free_data(data, "Error: Invalid number of arguments of a cylinder.\n");
	}
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
