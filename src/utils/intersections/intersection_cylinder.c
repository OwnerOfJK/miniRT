/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_cylinder.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 15:22:54 by jkaller           #+#    #+#             */
/*   Updated: 2024/08/01 12:28:09 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

bool static solve_quadratic_cyy(double abc[3], double *t1, double *t2)
{
	double	discriminant;

	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (false);
	else if (discriminant == 0)
	{
		*t1 = -b / (2 * a);
		*t2 = -b / (2 * a);
	}
	else
	{
		*t1 = (-b - sqrt(discriminant)) / (2 * a);
		*t2 = (-b + sqrt(discriminant)) / (2 * a);
	}
	return (true);
}

double	cylinder_tube(t_object *cy, t_ray *ray)
{
	t_vector		cylinder_to_ray;
	double			radius;
	double			roots[2];
	double			abc[3];
	double			y[2];

	radius = cy->shape.cylinder.diameter / 2;
	cylinder_to_ray = v_sub(ray->origin, cy->pos);
	abc[0] = v_dot(ray->direction, ray->direction) - pow(v_dot(ray->direction, cy->shape.cylinder.axis_vector), 2);
	abc[1] = 2 * (v_dot(ray->direction, cylinder_to_ray) - (v_dot(ray->direction, cy->shape.cylinder.axis_vector) * v_dot(cylinder_to_ray, cy->shape.cylinder.axis_vector)));
	abc[2] = v_dot(cylinder_to_ray, cylinder_to_ray) - pow(v_dot(cylinder_to_ray, cy->shape.cylinder.axis_vector), 2) - pow(radius, 2);
	if (!solve_quadratic_cyy(abc, &roots[0], &roots[1]))
		return (-1);
	y[0] = v_dot(ray->direction, cy->shape.cylinder.axis_vector) * roots[0] + v_dot(cylinder_to_ray, cy->shape.cylinder.axis_vector);
	y[1] = v_dot(ray->direction, cy->shape.cylinder.axis_vector) * roots[1] + v_dot(cylinder_to_ray, cy->shape.cylinder.axis_vector);
	if (roots[0] > EPSILON && y[0] >= -cy->shape.cylinder.height / 2 && y[0] <= cy->shape.cylinder.height / 2)
		return (roots[0]);
	else if (roots[1] > EPSILON && y[1] >= -cy->shape.cylinder.height / 2 && y[1] <= cy->shape.cylinder.height / 2)
	return (roots[1]);
	else
		return (-1);
}

void	cylinder_intersect(t_object *cy, t_ray *ray,
	t_intersections *intersection)
{
	t_ray	object_space_ray;
	double	t_tube;

	object_space_ray = ray_transform(ray, cy->inverse_matrix);
	t_tube = cylinder_tube(cy, &object_space_ray);
	if (t_tube > EPSILON && t_tube < intersection->t1)
	{
		intersection->t1 = t_tube;
		intersection->count = 1;
		intersection->hit = 1;
		intersection->color = cy->color;
		intersection->object = cy;
		intersection->intersection_point
			= ray_position(&object_space_ray, t_tube);
	}
}
