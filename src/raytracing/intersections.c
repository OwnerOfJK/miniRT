/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:07:42 by ecarlier          #+#    #+#             */
/*   Updated: 2024/06/16 18:35:14 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"


// /* This function is not called yet*/
// int	 intersection()
// {
// 	return 0;
// }

// /*
// NEED TESTING
// sp : pointer to the sphere
// ray : pointer to the ray


// We need to use the radius of the sphere and not his diameter
// 		d = 2r
//  < = >  r = d/2

// if delta < 0
// 	no intersection
// if delta = 0
// 	2 intersections
// if delta > 0
// 	1 intersection

// delta is stored in the return value of solve_quadratic

// t1 and t2 is updated in solve_quadratic

// -> don't know what the next step is

// use of epsilon to avoid edge cases
// */
// int	sphere_intersect(t_sphere *sp, t_ray *ray)
// {
// 	t_equat2 equat2;
// 	t_vector o_c; //ray's origin - center of the sphere
// 	double	radius;

// 	radius = (sp->diameter / 2);
// 	equat2.t1 = -1; //random negative value -> meaning no intersection to begin with
// 	o_c = v_sub(ray->origin, sp->pos);
// 	equat2.a = v_dot(ray->direction, ray->direction);
// 	equat2.b = 2.0 * v_dot(ray->direction, o_c);
// 	equat2.c = v_dot(o_c, o_c) - (radius * radius);
// 	if (solve_quadratic(&equat2) > 0 && (equat2.t1 > EPSILON
// 			|| equat2.t2 > EPSILON))
// 	{
// 		//need to analyse the solution and put it smw so it can be used
// 	}
// 	return (0);
// }
// /*

// 4 cases :
// ray is // -> no intersection -> we check that with the scalar product
// ray is coplanar -> infinite intersections
// ray origin is above the plane
// ray origin is below the plane
// */
// int	plane_intersect(t_plane *pl, t_ray *ray)
// {
// 	t_vector	o_p;
// 	double		numerator;
// 	double		denominator;

// 	o_p = v_sub(ray->origin, pl->pos);
// 	if (v_dot(ray->direction, pl->normal_vector) != 0)
// 	{
// 		denominator = v_dot(pl->normal_vector, ray->direction);
// 		if (denominator == 0) //not neccesasry
// 			return (-1);
// 		numerator = -1 * v_dot(o_p, pl->normal_vector);
// 		// t = umerator / denominator;
// 		// if ( t > 0)
// 			// one intersection
// 		// need to fill the hit stuct with t;
// 	}
// 	return (1);
// }
