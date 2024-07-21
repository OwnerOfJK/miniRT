/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_sphere.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 18:19:12 by ecarlier          #+#    #+#             */
/*   Updated: 2024/07/21 12:28:03 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

double	set_intersections_t2(double t1, double t2)
{
	double	temp;

	temp = 0;
	if (t1 > EPSILON && t2 > EPSILON)
	{
		if (t1 > t2)
		{
			temp = t1;
			t1 = t2;
			t2 = temp;
		}
	}
	if (t2 < EPSILON )
		return (-1);
	else
		return (t2);
}

double	set_intersections(double t1, double t2)
{
	double	temp;

	temp = 0;
	if (t1 > EPSILON && t2 > EPSILON)
	{
		if (t1 > t2)
		{
			temp = t1;
			t1 = t2;
			t2 = temp;
		}
	}
	else if (t2 > EPSILON)
	{
		t1 = t2;
	}
	return (t1);
}

// t_intersections *sphere_intersect(t_object *sp, t_ray *ray)
// {
// 	t_intersections *intersections;
// 	t_equat2 equat2;
// 	t_vector sphere_to_ray;
// 	double radius;
// 	double delta;
// 	double** inverse_transform;
// 	t_ray object_space_ray;

// 	intersections = malloc(sizeof(t_intersections));
// 	// Initialize intersections
// 	intersections->count = 0;
// 	intersections->hit = 0;
// 	// Inverse transformation matrix
// 	inverse_transform = m_inverse(sp->transformation_matrix);
// 	// Transform the ray into object space
// 	object_space_ray = ray_transform(ray, inverse_transform);
// 	// Sphere radius
// 	radius = (sp->shape.sphere.diameter / 2);
// 	// Compute sphere_to_ray vector in object space
// 	sphere_to_ray = v_sub(object_space_ray.origin, v_init(0, 0, 0, 1));
// 	// Quadratic equation coefficients
// 	equat2.a = v_dot(object_space_ray.direction, object_space_ray.direction);
// 	equat2.b = 2.0 * v_dot(object_space_ray.direction, sphere_to_ray);
// 	equat2.c = v_dot(sphere_to_ray, sphere_to_ray) - (radius * radius);
// 	// Solve quadratic equation
// 	delta = solve_quadratic(&equat2);
// 	if (delta >= 0)
// 	{
// 		// Set intersection points
// 		set_intersections(equat2.t1, equat2.t2, intersections);
// 		intersections->count = 1;
// 		intersections->hit = 1;
// 		intersections->color = sp->color;
// 		intersections->object = sp;
// 	}
// 	free_matrix(inverse_transform);
// 	return (intersections);
// }


void	sphere_intersect(t_object *sp, t_ray *ray, t_intersections *intersection)
{
	t_vector sphere_to_ray;
	double radius;
	double** inverse_transform;
	t_ray object_space_ray;

	double a,b,c, t1;

	inverse_transform = m_inverse(sp->transformation_matrix);

	// Transform the ray into object space
	object_space_ray = ray_transform(ray, inverse_transform);

	radius = (sp->shape.sphere.diameter / 2);

	// Compute sphere_to_ray vector in object space
	sphere_to_ray = v_sub(object_space_ray.origin, v_init(0, 0, 0, 1));

	a = v_dot(object_space_ray.direction, object_space_ray.direction);
	b = 2.0 * v_dot(object_space_ray.direction, sphere_to_ray);
	c = v_dot(sphere_to_ray, sphere_to_ray) - (radius * radius);

	t1 = solve_quadratic(a, b, c);
	//intersections->t1 = t1;

	if (t1 > EPSILON)
	{
		if (t1 < intersection->t1)
		{
			intersection->t1 = t1;
			intersection->count = 1;
			intersection->hit = 1;
			intersection->color = sp->color;
			intersection->object = sp;
		}
	}
	free_matrix(inverse_transform);
}
