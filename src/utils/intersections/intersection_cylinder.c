/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_cylinder.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 15:22:54 by jkaller           #+#    #+#             */
/*   Updated: 2024/06/26 14:42:47 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

t_intersections	*cylinder_intersect(t_object *cy, t_ray *ray)
{
	t_intersections	*intersections;
	t_equat2		equat;
	t_vector		cylinder_to_ray;
	double			radius;
	double			delta;
	double**		inverse_transform;
    t_ray			object_space_ray;

	intersections = malloc(sizeof(t_intersections));
	// Initialize intersections
    intersections->count = 0;
    intersections->hit = 0;

	// Inverse transformation matrix
    inverse_transform = m_inverse(cy->transformation_matrix);
    // Transform the ray into object space
    object_space_ray = ray_transform(ray, inverse_transform);

	radius = cy->shape.cylinder.diameter / 2;

	// Compute cylinder_to_ray vector in object space
	cylinder_to_ray = v_sub(ray->origin, cy->shape.cylinder.cap_down);
	// Quadratic equation coefficients
  	equat.a = v_dot(ray->direction, ray->direction) - (v_dot(ray->direction, cy->shape.cylinder.axis_vector) * v_dot(ray->direction, cy->shape.cylinder.axis_vector));
    equat.b = 2 * (v_dot(ray->direction, cylinder_to_ray) - (v_dot(ray->direction, cy->shape.cylinder.axis_vector) * v_dot(cylinder_to_ray, cy->shape.cylinder.axis_vector)));
	equat.c = v_dot(cylinder_to_ray, cylinder_to_ray) - (v_dot(cylinder_to_ray, cy->shape.cylinder.axis_vector) * v_dot(cylinder_to_ray, cy->shape.cylinder.axis_vector)) - (radius * radius);
	// Solve quadratic equation

	delta = solve_quadratic(&equat);

	if (delta >= 0)
	{
		set_intersections(equat.t1, equat.t2, intersections);
		intersections->count = 1;
		intersections->hit = 1;
		intersections->color = cy->color;
		intersections->object = cy;
	}
	free_matrix(inverse_transform);
	return (intersections);
}
