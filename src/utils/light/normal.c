/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 11:53:17 by jkaller           #+#    #+#             */
/*   Updated: 2024/08/05 22:44:28 by ecarlier         ###   ########.fr       */
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
	if (v_dot(ray->direction, object->u_shape.s_plane.normal_vector) > 0)
		return (neg(object->u_shape.s_plane.normal_vector));
	else
		return (object->u_shape.s_plane.normal_vector);
}

t_vector	compute_cylinder(t_object *object, t_vector world_point)
{
	t_vector	pc;
	t_vector	normal;
	t_vector	projection;
	t_vector	world_normal;
	double		**inverse_transpose;

	pc = v_sub(mv_mult(object->inverse_matrix, world_point), object->pos);
	projection = v_scalar(object->u_shape.s_cylinder.axis_vector,
			v_dot(pc, object->u_shape.s_cylinder.axis_vector));
	normal = v_sub(pc, projection);
	normal = v_normalize(normal);
	inverse_transpose = m_transpose(object->inverse_matrix);
	world_normal = mv_mult(inverse_transpose, normal);
	world_normal = v_normalize(world_normal);
	free_matrix(inverse_transpose);
	return (world_normal);
}

t_vector	normal_at(t_intersections *intersection, t_ray *ray)
{
	double		t;
	t_vector	normal_vector;
	t_vector	world_point;

	t = intersection->t1;
	intersection->intersection_point = ray_position(ray, t);
	world_point = intersection->intersection_point;
	intersection->ray = *ray;
	normal_vector = v_init(0, 0, 0, 0);
	if (intersection->object->type == SPHERE)
		normal_vector = compute_sphere(intersection->object, world_point);
	else if (intersection->object->type == PLANE)
		normal_vector = compute_plane(intersection->object, &intersection->ray);
	else if (intersection->object->type == CYLINDER)
		normal_vector = compute_cylinder(intersection->object, world_point);
	return (normal_vector);
}
