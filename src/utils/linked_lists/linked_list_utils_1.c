/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_utils_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 00:23:57 by jkaller           #+#    #+#             */
/*   Updated: 2024/08/05 21:52:03 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

t_object	*add_sphere(t_context *ctx, t_object *object, char *save_pointer)
{
	object = malloc(sizeof(t_object));
	if (object == NULL)
		error_free_data(ctx->data, "Error: Memory allocation failed.\n");
	object->type = SPHERE;
	if (check_nb_arg(save_pointer, 3))
	{
		free(object);
		free(ctx->tmp);
		free_objects(ctx->objects_head);
		error_free_data(ctx->data,
			"Error: Invalid number of arguments of a sphere.\n");
	}
	parse_sphere_attributes(object, save_pointer);
	object->transformation_matrix = m_translate(object->pos);
	object->inverse_matrix = m_inverse(object->transformation_matrix);
	return (object);
}

t_object	*add_plane(t_context *ctx, t_object *object, char *save_pointer)
{
	object = malloc(sizeof(t_object));
	if (object == NULL)
		error_free_data(ctx->data, "Error: Memory allocation failed.\n");
	object->type = PLANE;
	if (check_nb_arg(save_pointer, 3))
	{
		free(object);
		free(ctx->tmp);
		free_objects(ctx->objects_head);
		error_free_data(ctx->data,
			"Error: Invalid number of arguments of a plane.\n");
	}
	parse_plane_attributes(object, save_pointer);
	object->transformation_matrix = m_translate(object->pos);
	object->inverse_matrix = m_inverse(object->transformation_matrix);
	return (object);
}

t_object	*add_cylinder(t_context *ctx, t_object *object, char *save_pointer)
{
	object = malloc(sizeof(t_object));
	if (object == NULL)
		error_free_data(ctx->data, "Error: Memory allocation failed.\n");
	object->type = CYLINDER;
	if (check_nb_arg(save_pointer, 5))
	{
		free(object);
		free(ctx->tmp);
		free_objects(ctx->objects_head);
		error_free_data(ctx->data,
			"Error: Invalid number of arguments of a cylinder.\n");
	}
	parse_cylinder_attributes(object, save_pointer);
	// compute_cylinder_m(object);
	return (object);
}
