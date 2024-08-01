/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_cylinder.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 15:22:54 by jkaller           #+#    #+#             */
/*   Updated: 2024/08/01 12:42:04 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

bool static	solve_quadratic_cyy(double abc[3], double *t1, double *t2)
{
	double	discriminant;

	discriminant = abc[1] * abc[1] - 4 * abc[0] * abc[2];
	if (discriminant < 0)
		return (false);
	else if (discriminant == 0)
	{
		*t1 = -abc[1] / (2 * abc[0]);
		*t2 = -abc[1] / (2 * abc[0]);
	}
	else
	{
		*t1 = (-abc[1] - sqrt(discriminant)) / (2 * abc[0]);
		*t2 = (-abc[1] + sqrt(discriminant)) / (2 * abc[0]);
	}
	return (true);
}

double static	cylinder_tube(t_object *cy, t_ray *ray, double radius)
{
	t_vector		cr;
	double			roots[2];
	double			abc[3];
	double			y[2];
	t_vector		axis;

	axis = cy->shape.cylinder.axis_vector;
	cr = v_sub(ray->origin, cy->pos);
	abc[0] = v_dot(ray->direction, ray->direction)
		- pow(v_dot(ray->direction, axis), 2);
	abc[1] = 2 * (v_dot(ray->direction, cr)
			- (v_dot(ray->direction, axis) * v_dot(cr, axis)));
	abc[2] = v_dot(cr, cr) - pow(v_dot(cr, axis), 2) - pow(radius, 2);
	if (!solve_quadratic_cyy(abc, &roots[0], &roots[1]))
		return (-1);
	y[0] = v_dot(ray->direction, axis) * roots[0] + v_dot(cr, axis);
	y[1] = v_dot(ray->direction, axis) * roots[1] + v_dot(cr, axis);
	if (roots[0] > EPSILON && y[0] >= -cy->shape.cylinder.height / 2 && y[0]
		<= cy->shape.cylinder.height / 2)
		return (roots[0]);
	else if (roots[1] > EPSILON && y[1] >= -cy->shape.cylinder.height / 2
		&& y[1] <= cy->shape.cylinder.height / 2)
		return (roots[1]);
	else
		return (-1);
}

void	cylinder_intersect(t_object *cy, t_ray *ray,
	t_intersections *intersection)
{
	t_ray	object_space_ray;
	double	t_tube;
	double	radius;

	object_space_ray = ray_transform(ray, cy->inverse_matrix);
	radius = cy->shape.cylinder.diameter / 2;
	t_tube = cylinder_tube(cy, &object_space_ray, radius);
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
