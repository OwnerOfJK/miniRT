/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_sphere.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 18:19:12 by ecarlier          #+#    #+#             */
/*   Updated: 2024/08/05 22:43:52 by ecarlier         ###   ########.fr       */
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

void	sphere_intersect(t_object *sp, t_ray *ray,
	t_intersections *intersection)
{
	t_vector	sphere_to_ray;
	double		radius;
	t_ray		object_space_ray;
	double		abct1[4];

	object_space_ray = ray_transform(ray, sp->inverse_matrix);
	radius = (sp->u_shape.s_sphere.diameter / 2);
	sphere_to_ray = v_sub(object_space_ray.origin, v_init(0, 0, 0, 1));
	abct1[0] = v_dot(object_space_ray.direction, object_space_ray.direction);
	abct1[1] = 2.0 * v_dot(object_space_ray.direction, sphere_to_ray);
	abct1[2] = v_dot(sphere_to_ray, sphere_to_ray) - (radius * radius);
	abct1[3] = solve_quadratic(abct1[0], abct1[1], abct1[2]);
	if (abct1[3] > EPSILON)
	{
		if (abct1[3] < intersection->t1)
		{
			intersection->t1 = abct1[3];
			intersection->count = 1;
			intersection->hit = 1;
			intersection->color = sp->color;
			intersection->object = sp;
		}
	}
}
