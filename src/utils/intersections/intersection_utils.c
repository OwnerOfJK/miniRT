/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 20:43:09 by jkaller           #+#    #+#             */
/*   Updated: 2024/07/21 14:20:20 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

t_intersections	*object_intersection(t_object *objects, t_ray *ray)
{
	// t_intersections	*pl_intersection;
	// t_intersections	*sp_intersection;
	// t_intersections	*cy_intersection;
	t_intersections	*intersection;
	int				i;

	intersection = ft_calloc(sizeof(t_intersections), 1);
	intersection->t1 = DBL_MAX;
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
	return (intersection);
}


