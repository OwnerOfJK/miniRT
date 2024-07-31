/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 11:53:17 by jkaller           #+#    #+#             */
/*   Updated: 2024/07/31 18:23:00 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

t_vector	compute_sphere(t_object	*object, t_vector world_point)
{
	t_vector	normal;
	t_vector	object_point;
	t_vector	world_normal;
	double		**inverse_transpose;

	object_point = mv_mult(object->inverse_matrix, world_point);
	inverse_transpose = m_transpose(object->inverse_matrix);
	normal = v_sub(object_point, v_init(0, 0, 0, 1));
	normal = v_normalize(normal);
	world_normal = mv_mult(inverse_transpose, normal);
	normal = v_normalize(world_normal);
	free_matrix(inverse_transpose);
	return (normal);
}

t_vector	compute_plane(t_object	*object, t_ray *ray)
{
	if (v_dot(ray->direction, object->shape.plane.normal_vector) > 0)
		return (neg(object->shape.plane.normal_vector));
	else
		return (object->shape.plane.normal_vector);
}

t_vector	compute_cylinder(t_object *object, t_vector local_point)
{
	t_vector pc;
	t_vector normal;

	// Compute vector from cylinder center to intersection point
	pc = v_sub(local_point, object->pos);
	// Project pc onto the axis vector of the cylinder
	t_vector projection = v_scalar(object->shape.cylinder.axis_vector, v_dot(pc, object->shape.cylinder.axis_vector));
	// Calculate the normal as the difference between pc and the projection
	normal = v_sub(pc, projection);

	// Transform the normal back to world space
	// We use the transpose of the inverse matrix to correctly transform the normal
	normal = mv_mult(m_transpose(object->inverse_matrix), normal);
	// Ensure the result is treated as a vector, not a point
	normal.w = 0;
	// Normalize the vector to ensure it has unit length
	normal = v_normalize(normal);
	
	return (normal);
}

t_vector	normal_at(t_intersections *intersection, t_ray *ray)
{
	double		t;
	t_vector	local_point;
	t_vector	normal_vector;
	t_vector	world_point;

	// Get the distance along the ray to the intersection point
	t = intersection->t1;
	intersection->intersection_point = ray_position(ray, t);
	// Calculate the actual intersection point in world space
	world_point = intersection->intersection_point;
	// Store the ray information in the intersection structure
	intersection->ray = *ray;
	// Initialize the normal vector
	normal_vector = v_init(0, 0, 0, 0);
	if (intersection->object->type == SPHERE) // For spheres, compute the normal directly in world space, This works because spheres are symmetrical
		normal_vector = compute_sphere(intersection->object, world_point);
	else if (intersection->object->type == PLANE) // For planes, compute the normal based on the plane's orientation. This is typically a constant normal for the entire plane
		normal_vector = compute_plane(intersection->object, &intersection->ray);
	else if (intersection->object->type == CYLINDER)
	{
		// For cylinders, we need to account for their orientation in space
		// Transform the intersection point from world space to object space
		local_point = mv_mult(intersection->object->inverse_matrix, world_point);
		// Compute the normal in object space
		normal_vector = compute_cylinder(intersection->object, local_point);
	}
	return (normal_vector);
}
