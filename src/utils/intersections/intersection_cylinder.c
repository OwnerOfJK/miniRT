/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_cylinder.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 15:22:54 by jkaller           #+#    #+#             */
/*   Updated: 2024/07/09 16:39:15 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"


double	cylinder_tube(t_object *cy, t_ray *ray)
{
	t_vector		cylinder_to_ray;
	double			radius;

	double a, b, c, t1, t2, y0, y1;

	radius = cy->shape.cylinder.diameter / 2;
	// cylinder_to_ray = v_sub(ray->origin, cy->shape.cylinder.cap_down);
	cylinder_to_ray = v_sub(ray->origin, cy->pos);
	a = v_dot(ray->direction, ray->direction) - (v_dot(ray->direction, cy->shape.cylinder.axis_vector) * v_dot(ray->direction, cy->shape.cylinder.axis_vector));
	b = 2 * (v_dot(ray->direction, cylinder_to_ray) - (v_dot(ray->direction, cy->shape.cylinder.axis_vector) * v_dot(cylinder_to_ray, cy->shape.cylinder.axis_vector)));
	c = v_dot(cylinder_to_ray, cylinder_to_ray) - (v_dot(cylinder_to_ray, cy->shape.cylinder.axis_vector) * v_dot(cylinder_to_ray, cy->shape.cylinder.axis_vector)) - (radius * radius);
	t1 = solve_quadratic(a, b, c);
	t2 = solve_quadratic_t2(a, b, c);
	if (t1 > EPSILON)
	{
		// y0 = v_dot(ray->direction,cy->shape.cylinder.axis_vector) * v_dot(ray->direction, cy->shape.cylinder.axis_vector) * t1 + v_dot(cylinder_to_ray, cy->shape.cylinder.axis_vector) * v_dot(ray->direction, cy->shape.cylinder.axis_vector);
		// y1 = v_dot(ray->direction, cy->shape.cylinder.axis_vector) * v_dot(ray->direction, cy->shape.cylinder.axis_vector) * t2 + v_dot(cylinder_to_ray, cy->shape.cylinder.axis_vector) * v_dot(ray->direction, cy->shape.cylinder.axis_vector);
		y0 = v_dot(ray->direction,cy->shape.cylinder.axis_vector) * t1 + v_dot(cylinder_to_ray, cy->shape.cylinder.axis_vector);
		y1 = v_dot(ray->direction,cy->shape.cylinder.axis_vector) * t2 +  v_dot(cylinder_to_ray, cy->shape.cylinder.axis_vector);
		if (y0 >= cy->shape.cylinder.height / - 2 && y0 <= cy->shape.cylinder.height / 2 )
			return (t1);
		else if ( y1 >= cy->shape.cylinder.height / - 2 && y1 <= cy->shape.cylinder.height/ 2 )
			return (t2);
		else
			return (-1);
	}
	else
		return (-1);
}

// double	cylinder_cap_up()
// {

// }

// double	cylinder_cap_down()
// {

// }

double	min_of_three(double a, double b, double c)
{
	double	min;

	min = a;
	if (b < min)
		min = b;
	if (c < min)
		min = c;
	return (min);
}

/* attention si pas d'inter -1, */
t_intersections	*cylinder_intersect(t_object *cy, t_ray *ray)
{
	t_intersections	*inter;
	double			t_tube;
	// double			t_cap_up;
	// double			t_cap_down;
	// double			t_closest;


//		@JOHN you added this but never used it after ?
//     inverse_transform = m_inverse(cy->transformation_matrix);
//     object_space_ray = ray_transform(ray, inverse_transform);


	inter = malloc(sizeof(t_intersections));
	inter->count = 0;
	inter->hit = 0;

	t_tube = cylinder_tube(cy, ray);

	// t_cap_up = cylinder_cap_up();
	// t_cap_down = cylinder_cap_down();


	if (t_tube > EPSILON)
	{
		inter->t1 = t_tube;
		inter->count = 1;
		inter->hit = 1;
		inter->color = cy->color;
		inter->object = cy;
	}
	return (inter);
}

// void	set_top_bottom(t_object *obj)
// {
// 	t_vector	half_height;
// 	t_vector	axis_vector;
// 	double		height;

// 	if (obj->type != CYLINDER)
// 		return ;

// 	axis_vector = obj->shape.cylinder.axis_vector;
// 	height = obj->shape.cylinder.height;

// 	half_height = v_scalar(axis_vector, height / 2);

// 	obj->shape.cylinder.top_plane.normal_vector = axis_vector;
// 	obj->shape.cylinder.top_plane.pos = v_sub(obj->pos, half_height);

// 	obj->shape.cylinder.bottom_plane.normal_vector = axis_vector;
// 	obj->shape.cylinder.bottom_plane.pos = v_sub(obj->pos, half_height);
// }
