/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_cylinder.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 15:22:54 by jkaller           #+#    #+#             */
/*   Updated: 2024/07/21 16:06:16 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"


// double	cylinder_tube(t_object *cy, t_ray *ray)
// {
// 	t_vector		cylinder_to_ray;
// 	double			radius;

// 	double a, b, c, t1, t2, y0, y1;

// 	radius = cy->shape.cylinder.diameter / 2;
// 	// cylinder_to_ray = v_sub(ray->origin, cy->shape.cylinder.cap_down);
// 	cylinder_to_ray = v_sub(ray->origin, cy->pos);
// 	a = v_dot(ray->direction, ray->direction) - (v_dot(ray->direction, cy->shape.cylinder.axis_vector) * v_dot(ray->direction, cy->shape.cylinder.axis_vector));
// 	b = 2 * (v_dot(ray->direction, cylinder_to_ray) - (v_dot(ray->direction, cy->shape.cylinder.axis_vector) * v_dot(cylinder_to_ray, cy->shape.cylinder.axis_vector)));
// 	c = v_dot(cylinder_to_ray, cylinder_to_ray) - (v_dot(cylinder_to_ray, cy->shape.cylinder.axis_vector) * v_dot(cylinder_to_ray, cy->shape.cylinder.axis_vector)) - (radius * radius);
// 	t1 = solve_quadratic(a, b, c);
// 	t2 = solve_quadratic_t2(a, b, c);
// 	if (t1 > EPSILON)
// 	{
// 		// y0 = v_dot(ray->direction,cy->shape.cylinder.axis_vector) * v_dot(ray->direction, cy->shape.cylinder.axis_vector) * t1 + v_dot(cylinder_to_ray, cy->shape.cylinder.axis_vector) * v_dot(ray->direction, cy->shape.cylinder.axis_vector);
// 		// y1 = v_dot(ray->direction, cy->shape.cylinder.axis_vector) * v_dot(ray->direction, cy->shape.cylinder.axis_vector) * t2 + v_dot(cylinder_to_ray, cy->shape.cylinder.axis_vector) * v_dot(ray->direction, cy->shape.cylinder.axis_vector);
// 		y0 = v_dot(ray->direction,cy->shape.cylinder.axis_vector) * t1 + v_dot(cylinder_to_ray, cy->shape.cylinder.axis_vector);
// 		y1 = v_dot(ray->direction,cy->shape.cylinder.axis_vector) * t2 +  v_dot(cylinder_to_ray, cy->shape.cylinder.axis_vector);
// 		if (y0 >= cy->shape.cylinder.height / - 2 && y0 <= cy->shape.cylinder.height / 2 )
// 			return (t1);
// 		else if ( y1 >= cy->shape.cylinder.height / - 2 && y1 <= cy->shape.cylinder.height/ 2 )
// 			return (t2);
// 		else
// 			return (-1);
// 	}
// 	else
// 		return (-1);
// }

// // double	cylinder_cap_up()
// // {

// // }

// // double	cylinder_cap_down()
// // {

// // }

// double	min_of_three(double a, double b, double c)
// {
// 	double	min;

// 	min = a;
// 	if (b < min)
// 		min = b;
// 	if (c < min)
// 		min = c;
// 	return (min);
// }

// /* attention si pas d'inter -1, */
// void	cylinder_intersect(t_object *cy, t_ray *ray, t_intersections *intersection)
// {
// 	double			t_tube;
// 	// double			t_cap_up;
// 	// double			t_cap_down;
// 	// double			t_closest;


// //		@JOHN you added this but never used it after ?
// //     inverse_transform = m_inverse(cy->transformation_matrix);
// //     object_space_ray = ray_transform(ray, inverse_transform);

// 	t_tube = cylinder_tube(cy, ray);

// 	// t_cap_up = cylinder_cap_up();
// 	// t_cap_down = cylinder_cap_down();


// 	if (t_tube > EPSILON)
// 	{
// 		if (t_tube < intersection->t1)
// 		{
// 			intersection->t1 = t_tube;
// 			intersection->count = 1;
// 			intersection->hit = 1;
// 			intersection->color = cy->color;
// 			intersection->object = cy;
// 		}
// 	}
// }

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



// t_ray	ray_transform(t_ray *ray, double **matrix)
// {
// 	t_ray	transformed_ray;

// 	transformed_ray.origin = mv_mult(matrix, ray->origin);
// 	transformed_ray.direction = mv_mult(matrix, ray->direction);
// 	return (transformed_ray);
// }


bool solve_quadratic_cyy(double a, double b, double c, double *t1, double *t2)
{
    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
        return false;
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
    return true;
}

double	cylinder_tube(t_object *cy, t_ray *ray)
{
    t_vector		cylinder_to_ray;
    double			radius;
    double			a, b, c, t1, t2, y0, y1;

    radius = cy->shape.cylinder.diameter / 2;
    cylinder_to_ray = v_sub(ray->origin, cy->pos);
    a = v_dot(ray->direction, ray->direction) - pow(v_dot(ray->direction, cy->shape.cylinder.axis_vector), 2);
    b = 2 * (v_dot(ray->direction, cylinder_to_ray) - (v_dot(ray->direction, cy->shape.cylinder.axis_vector) * v_dot(cylinder_to_ray, cy->shape.cylinder.axis_vector)));
    c = v_dot(cylinder_to_ray, cylinder_to_ray) - pow(v_dot(cylinder_to_ray, cy->shape.cylinder.axis_vector), 2) - pow(radius, 2);

    // Solve the quadratic equation a*t^2 + b*t + c = 0
    if (!solve_quadratic_cyy(a, b, c, &t1, &t2)) // Ensure the function returns a bool for two valid roots
        return (-1);

    // Checking valid intersections by computing the coordinates along the cylinder height
    y0 = v_dot(ray->direction, cy->shape.cylinder.axis_vector) * t1 + v_dot(cylinder_to_ray, cy->shape.cylinder.axis_vector);
    y1 = v_dot(ray->direction, cy->shape.cylinder.axis_vector) * t2 + v_dot(cylinder_to_ray, cy->shape.cylinder.axis_vector);

    if (t1 > EPSILON && y0 >= -cy->shape.cylinder.height / 2 && y0 <= cy->shape.cylinder.height / 2)
        return (t1);
    else if (t2 > EPSILON && y1 >= -cy->shape.cylinder.height / 2 && y1 <= cy->shape.cylinder.height / 2)
        return (t2);
    else
        return (-1);
}

void cylinder_intersect(t_object *cy, t_ray *ray, t_intersections *intersection)
{
    t_ray object_space_ray;
    double t_tube;

    object_space_ray = ray_transform(ray, cy->inverse_matrix); // Transform ray into object space

    t_tube = cylinder_tube(cy, &object_space_ray); // Check for intersections

    if (t_tube > EPSILON && t_tube < intersection->t1)
    {
        intersection->t1 = t_tube;
        intersection->count = 1;
        intersection->hit = 1;
        intersection->color = cy->color;
        intersection->object = cy;
        
        // Calculate intersection point in object space
        intersection->intersection_point = ray_position(&object_space_ray, t_tube);
    }
}