/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_utils_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 00:23:57 by jkaller           #+#    #+#             */
/*   Updated: 2024/08/01 14:37:40 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

void	check_nb_arg(char *save_pointer, int nb)
{
	int			arg_count;
	char		*token;
	char		*temp;
	int			i;
	char		*to_free;

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
		error_message("Error: Invalid number of arguments of a parameter.\n");
	}


// void	check_nb_arg(char *save_pointer, int nb)
// {
// 	int			arg_count;
// 	char		*token;
// 	char		*temp;
// 	char		*tofree;
// 	int			i;

// 	printf("nb : %i", nb);
// 	temp = ft_strdup(save_pointer);
// 	tofree = temp;
// 	arg_count = 0;
// 	i = 0;
// 	token = ft_strtok_r(NULL, " ", &temp);
// 	while (token != NULL && i <= nb)
// 	{
// 		arg_count++;
// 		token = ft_strtok_r(NULL, " ", &temp);
// 	}
// 	free(tofree);
// 	if (arg_count != nb)
// 		error_message("Error: Invalid number of arguments of a parameter.\n");
// }

t_object	*add_sphere(t_object *object, char *save_pointer)
{
	char		*token;

	check_nb_arg(save_pointer, 3);
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

	check_nb_arg(save_pointer, 3);
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

t_object	*add_cylinder(t_object *object, char *save_pointer)
{
	char		*token;

	check_nb_arg(save_pointer, 5);
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
