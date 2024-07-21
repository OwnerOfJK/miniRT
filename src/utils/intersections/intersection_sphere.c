/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_sphere.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 18:19:12 by ecarlier          #+#    #+#             */
/*   Updated: 2024/07/21 15:23:38 by jkaller          ###   ########.fr       */
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
	if (t2 < EPSILON)
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

void	sphere_intersect(t_object *sp, t_ray *ray, t_intersections *intersection)
{
	t_vector sphere_to_ray;
	double radius;
	t_ray object_space_ray;

	double a,b,c, t1;

	// Transform the ray into object space
	object_space_ray = ray_transform(ray, sp->inverse_matrix);

	radius = (sp->shape.sphere.diameter / 2);

	// Compute sphere_to_ray vector in object space
	sphere_to_ray = v_sub(object_space_ray.origin, v_init(0, 0, 0, 1));

	a = v_dot(object_space_ray.direction, object_space_ray.direction);
	b = 2.0 * v_dot(object_space_ray.direction, sphere_to_ray);
	c = v_dot(sphere_to_ray, sphere_to_ray) - (radius * radius);

	t1 = solve_quadratic(a, b, c);
	
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
}
