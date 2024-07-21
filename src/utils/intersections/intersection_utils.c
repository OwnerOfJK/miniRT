/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 20:43:09 by jkaller           #+#    #+#             */
/*   Updated: 2024/07/21 12:18:02 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

t_intersections *object_intersection(t_object *objects, t_ray *ray)
{
	// t_intersections	*pl_intersection;
	// t_intersections	*sp_intersection;
	t_intersections	*cy_intersection;
	t_intersections	*intersection;
	int				i;

	intersection = malloc(sizeof(t_intersections));
	intersection->t1 = DBL_MAX;
	intersection->hit = 0;
	intersection->color = (t_color){0, 0, 0};
	i = 0;
	while (objects != NULL)
	{
		if (objects->type == PLANE)
			plane_intersect(objects, ray, intersection);
		else if (objects->type == SPHERE)
			sphere_intersect(objects, ray, intersection);
		else if (objects->type == CYLINDER)
		{
			cy_intersection = cylinder_intersect(objects, ray);
			if (cy_intersection->hit == 1)
			{
				if (cy_intersection->t1 < intersection->t1)
					intersection = cy_intersection;
			}
		}
		objects = objects->next;
	}
	return (intersection);
}
/*

Need to create a function to go through all the shapes
*/
