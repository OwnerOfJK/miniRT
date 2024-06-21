/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_utils_0.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 11:53:17 by jkaller           #+#    #+#             */
/*   Updated: 2024/06/21 12:31:53 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

t_vector	compute_sphere(t_object	*object, t_vector world_point)
{
	t_vector	normal;
	double		**inverse_transform;
	t_vector	object_point;
	t_vector	world_normal;

	inverse_transform = m_inverse(object->transformation_matrix);
	object_point = mv_mult(inverse_transform, world_point);
	normal = v_sub(object_point, v_init(0, 0, 0, 1));
	normal = v_normalize(normal);
	world_normal = mv_mult(m_transpose(inverse_transform), normal);
	normal = v_normalize(world_normal);
	free_matrix(inverse_transform);
	return (normal);
}

t_vector	compute_plane(t_object	*object)
{
	double		**inverse_transform;
	t_vector	transformed_normal;
	t_vector	normal;

	inverse_transform = m_inverse(object->transformation_matrix);
	transformed_normal = mv_mult(m_transpose(inverse_transform),
			object->shape.plane.normal_vector);
	normal = v_normalize(transformed_normal);
	free_matrix(inverse_transform);
	return (normal);
}

t_vector	compute_cylinder(t_object	*object, t_vector world_point)
{
	double		**inverse_transform;
	t_vector	cylinder_base_to_point;
	t_vector	world_normal;
	t_vector	object_point;
	t_vector	normal;

	inverse_transform = m_inverse(object->transformation_matrix);
	object_point = mv_mult(inverse_transform, world_point);
	cylinder_base_to_point = v_sub(object_point,
			v_init(0, 0, object_point.z, 1));
	normal = v_normalize(cylinder_base_to_point);
	world_normal = mv_mult(m_transpose(inverse_transform), normal);
	normal = v_normalize(world_normal);
	free_matrix(inverse_transform);
	return (normal);
}

t_vector	compute_normal(t_intersections *intersection)
{
	t_vector	normal;
	t_object	*object;
	t_vector	world_point;

	normal = v_init(0, 0, 0, 0);
	world_point = intersection->intersection_point;
	object = intersection->object;
	if (object->type == SPHERE)
		normal = compute_sphere(object, world_point);
	else if (object->type == PLANE)
		normal = compute_plane(object);
	else if (object->type == CYLINDER)
		normal = compute_cylinder(object, world_point);
	return (normal);
}

t_vector	normal_at(t_intersections *intersection, t_ray *ray)
{
	double		t;
	t_vector	normal_vector;

	t = intersection->t1;
	intersection->intersection_point = ray_position(ray, t);
	normal_vector = compute_normal(intersection);
	return (normal_vector);
}
