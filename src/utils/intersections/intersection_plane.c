/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_plane.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 18:16:39 by ecarlier          #+#    #+#             */
/*   Updated: 2024/06/16 22:09:43 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

t_intersections	plane_inter(t_plane *pl, t_ray *ray)
{
	t_intersections	intersect;
	t_intersections	temp;

	temp.hit = 0;
	intersect.hit = 0;
	temp.t1 = DBL_MAX; //not sure about this
	while (pl != NULL)
	{
		intersect = plane_intersect(pl, ray);

		if (intersect.count != 0)
		{
			intersect.hit = 1;
			if (intersect.t1 < temp.t1)
				temp = intersect;
		}
		pl = (t_plane *)pl->base.next;
	}
	if (intersect.hit == 1)
		return (intersect);
	else
		return (temp);
}


/*
4 cases :
ray is // -> no intersection -> we check that with the scalar product
ray is coplanar -> infinite intersections
ray origin is above the plane
ray origin is below the plane
*/
t_intersections	plane_intersect(t_plane *pl, t_ray *ray)
{
	t_intersections	intersections;
	t_vector		o_p;
	double			numerator;
	double			denominator;
	double			t;

	intersections.count = 0;

	o_p = v_sub(ray->origin, pl->pos);

	if (v_dot(ray->direction, pl->normal_vector) != 0)
	{

		denominator = v_dot(pl->normal_vector, ray->direction);
		// if (denominator == 0)
		// 	return (-1);
		numerator = -v_dot(o_p, pl->normal_vector);
		t = numerator / denominator;
		// printf("Numerator = %f\n", numerator);
		// printf("Denominator = %f\n", denominator);
		// printf("t = %f\n", t);
		if (t >= 0)
		{
			intersections.count = 1;
			printf("hit plane\n");
			intersections.t1 = numerator / denominator;
			intersections.color = pl->color;
		}
	}
	return (intersections);
}
