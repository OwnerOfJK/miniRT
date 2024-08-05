/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections_plane.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 18:16:39 by ecarlier          #+#    #+#             */
/*   Updated: 2024/08/05 22:44:28 by ecarlier         ###   ########.fr       */
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
void	plane_intersect(t_object *pl, t_ray *ray, t_intersections *intersection,
	double num_denom[2])
{
	t_vector		o_p;
	double			t;
	t_ray			object_space_ray;
	t_vector		t_normal;

	object_space_ray = ray_transform(ray, pl->inverse_matrix);
	t_normal = mv_mult(pl->inverse_matrix, pl->u_shape.s_plane.normal_vector);
	o_p = v_sub(object_space_ray.origin, pl->pos);
	num_denom[1] = v_dot(object_space_ray.direction, t_normal);
	if (num_denom[1] != 0)
	{
		num_denom[0] = -v_dot(o_p, t_normal);
		t = num_denom[0] / num_denom[1];
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
