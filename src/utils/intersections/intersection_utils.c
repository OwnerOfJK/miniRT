/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 20:43:09 by jkaller           #+#    #+#             */
/*   Updated: 2024/08/05 22:34:53 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

void	object_intersection(t_object *objects, t_ray *ray,
	t_intersections	*intersection)
{
	double	num_denom[2];

	num_denom[0] = 0;
	num_denom[1] = 0;
	intersection->t1 = LARGE_DOUBLE;
	intersection->count = 0;
	intersection->hit = 0;
	intersection->object = NULL;
	while (objects != NULL)
	{
		if (objects->type == PLANE)
			plane_intersect(objects, ray, intersection,
				num_denom);
		else if (objects->type == SPHERE)
			sphere_intersect(objects, ray, intersection);
		else if (objects->type == CYLINDER)
			cylinder_intersect(objects, ray, intersection);
		objects = objects->next;
	}
}
