/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_plane.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 18:16:39 by ecarlier          #+#    #+#             */
/*   Updated: 2024/06/19 18:30:01 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

// t_intersections	plane_inter(t_plane *pl, t_ray *ray)
// {
// 	t_intersections	intersect;
// 	t_intersections	temp;

// 	temp.hit = 0;
// 	intersect.hit = 0;
// 	temp.t1 = DBL_MAX; //not sure about this
// 	while (pl != NULL)
// 	{
// 		intersect = plane_intersect(pl, ray);
// 		if (intersect.count != 0)
// 		{
// 			intersect.hit = 1;
// 			if (intersect.t1 < temp.t1)
// 				temp = intersect;
// 		}
// 		pl = (t_plane *)pl->base.next;
// 	}
// 	if (intersect.hit == 1)
// 		return (intersect);
// 	else
// 		return (temp);
// }


/*
4 cases :
ray is // -> no intersection -> we check that with the scalar product
ray is coplanar -> infinite intersections
ray origin is above the plane
ray origin is below the plane
*/
t_intersections	*plane_intersect(t_object *pl, t_ray *ray)
{
    t_intersections	*intersections;
    t_vector		o_p;
    double			numerator;
    double			denominator;
    double			t;
    double**		inverse_transform;
    t_ray			object_space_ray;
    t_vector		transformed_normal;

    intersections = malloc(sizeof(t_intersections));
    if (!intersections)
        return (NULL);
    
    intersections->count = 0;
    intersections->hit = 0;

    // Inverse transformation matrix
    inverse_transform = m_inverse(pl->transformation_matrix);

    // Transform the ray into object space
    object_space_ray = ray_transform(ray, inverse_transform);

    // Transform the plane's normal vector to object space
    transformed_normal = mv_mult(inverse_transform, pl->shape.plane.normal_vector);

    // Compute ray-plane intersection in object space
    o_p = v_sub(object_space_ray.origin, pl->pos);
    denominator = v_dot(object_space_ray.direction, transformed_normal);
    
    if (denominator != 0) // Ensure the ray is not parallel to the plane
    {
        numerator = -v_dot(o_p, transformed_normal);
        t = numerator / denominator;

        if (t >= 0)
        {
            intersections->count = 1;
            intersections->hit = 1;
            intersections->t1 = t;
            intersections->color = pl->color;
			intersections->object = pl;
        }
    }

    // Free the inverse transformation matrix
    free_matrix(inverse_transform);

    return (intersections);
}
