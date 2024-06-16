/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 20:43:09 by jkaller           #+#    #+#             */
/*   Updated: 2024/06/16 20:53:37 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

void	set_intersections(double t1, double t2, t_intersections *intersections)
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
		intersections->t1 = t1;
		intersections->t2 = t2;
		intersections->count = 2;
	}
	else if (t1 > EPSILON)
	{
		intersections->t1 = t1;
		intersections->count = 1;
	}
	else if (t2 > EPSILON)
	{
		intersections->t1 = t2;
		intersections->count = 1;
	}
}

// t_intersections	sphere_intersections(t_sphere *sp, t_ray *ray)
// {
// 	t_intersections	intersections;
// 	t_equat2		equat2;
// 	t_vector		sphere_to_ray;
// 	double			radius;
// 	double			delta;

// 	radius = (sp->diameter / 2);
// 	sphere_to_ray = v_sub(ray->origin, sp->pos);
// 	equat2.a = v_dot(ray->direction, ray->direction);
// 	equat2.b = 2.0 * v_dot(ray->direction, sphere_to_ray);
// 	equat2.c = v_dot(sphere_to_ray, sphere_to_ray) - (radius * radius);
// 	delta = solve_quadratic(&equat2);
// 	intersections.count = 0;
// 	if (delta >= 0)
// 		set_intersections(equat2.t1, equat2.t2, &intersections);
// 	else
// 		intersections.count = 0;
// 	return (intersections);
// }

t_intersections sphere_intersections(t_sphere *sp, t_ray *ray)
{
    t_intersections intersections;
    t_equat2 equat2;
    t_vector sphere_to_ray;
    double radius;
    double delta;

    // Transform the ray into object space using the inverse of the sphere's transformation matrix
    double** inverse_transform = m_inverse(sp->transformation_matrix);
    t_ray object_space_ray = ray_transform(ray, inverse_transform);

    // Sphere is defined in object space (centered at origin with radius)
    radius = (sp->diameter / 2);
    sphere_to_ray = v_sub(object_space_ray.origin, v_init(0, 0, 0, 1));  // Object space

    equat2.a = v_dot(object_space_ray.direction, object_space_ray.direction);
    equat2.b = 2.0 * v_dot(object_space_ray.direction, sphere_to_ray);
    equat2.c = v_dot(sphere_to_ray, sphere_to_ray) - (radius * radius);
    delta = solve_quadratic(&equat2);
    
    intersections.count = 0;
    if (delta >= 0)
        set_intersections(equat2.t1, equat2.t2, &intersections);
    
    // Free the dynamically allocated inverse_transform matrix
    free_matrix(inverse_transform);
    return intersections;
}
