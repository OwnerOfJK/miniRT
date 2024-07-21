/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 11:53:17 by jkaller           #+#    #+#             */
/*   Updated: 2024/07/21 16:22:43 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

t_vector	compute_sphere(t_object	*object, t_vector world_point)
{
	t_vector	normal;
	t_vector	object_point;
	t_vector	world_normal;

	object_point = mv_mult(object->inverse_matrix, world_point);
	normal = v_sub(object_point, v_init(0, 0, 0, 1));
	normal = v_normalize(normal);
	world_normal = mv_mult(m_transpose(object->inverse_matrix), normal);
	normal = v_normalize(world_normal);
	return (normal);
}

// t_vector	compute_plane(t_object	*object)
// {
// 	double		**inverse_transform;
// 	t_vector	transformed_normal;
// 	t_vector	normal;

// 	inverse_transform = m_inverse(object->transformation_matrix);
// 	transformed_normal = mv_mult(m_transpose(inverse_transform),
// 			object->shape.plane.normal_vector);
// 	normal = v_normalize(transformed_normal);
// 	free_matrix(inverse_transform);
// 	return (normal);
// }
t_vector	compute_plane(t_object	*object, t_ray *ray)
{
	if (v_dot(ray->direction, object->shape.plane.normal_vector) > 0)
		return (neg(object->shape.plane.normal_vector));
	else
		return (object->shape.plane.normal_vector);
}

// t_vector	compute_cylinder(t_object	*object, t_vector world_point)
// {
// 	t_vector	pc;
// 	t_vector	normal;


// 	// t_vector	object_point;
// 	// double		**inverse_transform;

// 	// inverse_transform = m_inverse(object->transformation_matrix); //doesn't change anything
// 	// object_point = mv_mult(inverse_transform, world_point);

// 	pc = v_sub(world_point, object->pos);
// 	normal = v_sub(pc, v_scalar(object->shape.cylinder.axis_vector, v_dot(pc, object->shape.cylinder.axis_vector)));

// 	//free_matrix(inverse_transform);
// 	return (normal);
// }

t_vector compute_cylinder(t_object *object, t_vector local_point)
{
    t_vector pc, normal;

    // Compute vector from cylinder center to intersection point
    pc = v_sub(local_point, object->pos);

    // Project pc onto the axis vector of the cylinder
    t_vector projection = v_scalar(object->shape.cylinder.axis_vector, v_dot(pc, object->shape.cylinder.axis_vector));

    // Calculate the normal as the difference between pc and the projection
    normal = v_sub(pc, projection);

    return normal;
}

// t_vector	compute_cylinder(t_object	*object, t_vector world_point)
// {
// 	double		**inverse_transform;
// 	t_vector	cylinder_base_to_point;
// 	t_vector	world_normal;
// 	t_vector	object_point;
// 	t_vector	normal;

// 	inverse_transform = m_inverse(object->transformation_matrix);
// 	object_point = mv_mult(inverse_transform, world_point);

// 	cylinder_base_to_point = v_sub(object_point,
// 			v_init(0, 0, object_point.z, 1));

// 	normal = v_normalize(cylinder_base_to_point);
// 	world_normal = mv_mult(m_transpose(inverse_transform), normal);
// 	normal = v_normalize(world_normal);
// 	free_matrix(inverse_transform);
// 	return (normal);
// }

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
	// else if (object->type == PLANE)
	// 	normal = compute_plane(object);
	else if (object->type == PLANE)
	 	normal = compute_plane(object, &intersection->ray);
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
