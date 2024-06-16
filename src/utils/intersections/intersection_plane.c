/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_plane.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 18:16:39 by ecarlier          #+#    #+#             */
/*   Updated: 2024/06/16 18:17:01 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

/*

4 cases :
ray is // -> no intersection -> we check that with the scalar product
ray is coplanar -> infinite intersections
ray origin is above the plane
ray origin is below the plane
*/
int	plane_intersect(t_plane *pl, t_ray *ray)
{
	t_vector	o_p;
	double		numerator;
	double		denominator;

	o_p = v_sub(ray->origin, pl->pos);
	if (v_dot(ray->direction, pl->normal_vector) != 0)
	{
		denominator = v_dot(pl->normal_vector, ray->direction);
		if (denominator == 0) //not neccesasry
			return (-1);
		numerator = -1 * v_dot(o_p, pl->normal_vector);
		// t = umerator / denominator;
		// if ( t > 0)
			// one intersection
		// need to fill the hit stuct with t;
	}
	return (1);
}
