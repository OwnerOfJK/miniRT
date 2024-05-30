/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:07:42 by ecarlier          #+#    #+#             */
/*   Updated: 2024/05/30 20:33:15 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"


/* This function is not called yet*/
int	 intersection()
{
	return 0;
}

/*
NEED TESTING
sp : pointer to the sphere
ray : pointer to the ray


We need to use the radius of the sphere and not his diameter
		d = 2r
 < = >  r = d/2
*/
int	 sphere_intersect(t_sphere *sp, t_ray *ray)
{
	t_equat2 equat2;
	t_vector o_c; //ray's origin - center of the sphere
	double	radius;

	radius = (sp->diameter / 2);
	equat2.t1 = -1.0; //random negative value -> meaning no intersection to begin with
	o_c = v_sub(ray->origin, *sp->pos);
	equat2.a = v_dot(ray->direction, ray->direction);
	equat2.b = 2.0 * v_dot(ray->direction, o_c);
	equat2.c = v_dot(o_c, o_c) - (radius * radius);
	return 0;

}
