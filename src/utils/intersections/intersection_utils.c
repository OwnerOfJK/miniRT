/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 20:43:09 by jkaller           #+#    #+#             */
/*   Updated: 2024/06/20 15:33:45 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"


// t_intersections	shape_intersection(t_plane *pl, t_sphere *sp, t_ray *ray)
// {
// 	t_intersections	pl_inter;
// 	t_intersections	sp_inter;
// 	t_intersections	closest;

// 	pl_inter = plane_inter(pl, ray);
// 	sp_inter = spheres_inter(sp, ray);

// 	if (sp_inter.hit == 1 && pl_inter.hit == 1)
// 	{
// 		if (pl_inter.t1 < sp_inter.t1)
// 			closest = pl_inter;
// 		else
// 			closest = sp_inter;
// 	}
// 	else if (sp_inter.hit == 1 && pl_inter.hit == 0)
// 		closest = sp_inter;
// 	else if (sp_inter.hit == 0 && pl_inter.hit == 1)
// 		closest = sp_inter;
// }

t_intersections *object_intersection(t_object *objects, t_ray *ray)
{
	t_intersections	*pl_intersection;
	t_intersections	*sp_intersection;
	t_intersections	*closest;
	int i;

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
			sp_intersection = cylinder_intersect(objects, ray);
			if (sp_intersection->hit == 1)
			{
				if (sp_intersection->t1 < closest->t1)
					closest = sp_intersection;
			}
		}
		objects = objects->next;
	}
	return (closest);
}
/*

Need to create a function to go through all the shapes
*/
