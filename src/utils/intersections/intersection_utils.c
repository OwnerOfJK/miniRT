/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 20:43:09 by jkaller           #+#    #+#             */
/*   Updated: 2024/07/30 15:56:09 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

void	object_intersection(t_object *objects, t_ray *ray, t_intersections	*intersection)
{
	int				i;

	intersection->t1 = DBL_MAX;
	intersection->count = 0;
	intersection->hit = 0;
	i = 0;
	while (objects != NULL)
	{
		if (objects->type == PLANE)
			plane_intersect(objects, ray, intersection);
		else if (objects->type == SPHERE)
			sphere_intersect(objects, ray, intersection);
		else if (objects->type == CYLINDER)
			cylinder_intersect(objects, ray, intersection);
		objects = objects->next;
	}
}


