
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_plane.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 18:16:39 by ecarlier          #+#    #+#             */
/*   Updated: 2024/07/31 20:51:12 by ecarlier         ###   ########.fr       */
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
void	plane_intersect(t_object *pl, t_ray *ray, t_intersections *intersection)
{
	t_vector		o_p;
	double			numerator;
	double			denominator;
	double			t;
	t_ray			object_space_ray;
	t_vector		transformed_normal;


	object_space_ray = ray_transform(ray, pl->inverse_matrix);
	transformed_normal = mv_mult(pl->inverse_matrix, pl->shape.plane.normal_vector);
	o_p = v_sub(object_space_ray.origin, pl->pos);
	denominator = v_dot(object_space_ray.direction, transformed_normal);
	if (denominator != 0)
	{
		numerator = -v_dot(o_p, transformed_normal);
		t = numerator / denominator;
		if (t >= 0)
		{
			if (t < intersection->t1)
			{
				intersection->count = 1;
				intersection->hit = 1;
				intersection->t1 = t;
				intersection->color = pl->color;
				intersection->object = pl;
			}
		}
	}
}

