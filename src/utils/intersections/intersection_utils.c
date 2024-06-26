/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 20:43:09 by jkaller           #+#    #+#             */
/*   Updated: 2024/06/21 15:13:37 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

t_intersections *object_intersection(t_object *objects, t_ray *ray)
{
	t_intersections	*pl_intersection;
	t_intersections	*sp_intersection;
	t_intersections	*cy_intersection;
	t_intersections	*closest;
	int				i;

	closest = malloc(sizeof(t_intersections));
	closest->t1 = DBL_MAX;
	closest->hit = 0;
	closest->color = (t_color){0, 0, 0};
	i = 0;
	while (objects != NULL)
	{
		if (objects->type == PLANE)
		{
			pl_intersection = plane_intersect(objects, ray);
			if (pl_intersection->hit == 1)
			{
				if (pl_intersection->t1 < closest->t1)
					closest = pl_intersection;
			}
		}
		else if (objects->type == SPHERE)
		{
			sp_intersection = sphere_intersect(objects, ray);
			if (sp_intersection->hit == 1)
			{
				if (sp_intersection->t1 < closest->t1)
					closest = sp_intersection;
			}
		}
		else if (objects->type == CYLINDER)
		{
			cy_intersection = cylinder_intersect(objects, ray);
			if (cy_intersection->hit == 1)
			{
				if (cy_intersection->t1 < closest->t1)
					closest = cy_intersection;
			}
		}
		objects = objects->next;
	}
	return (closest);
}
/*

Need to create a function to go through all the shapes
*/
