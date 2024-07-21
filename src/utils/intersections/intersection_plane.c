/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_plane.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 18:16:39 by ecarlier          #+#    #+#             */
/*   Updated: 2024/07/21 12:17:57 by jkaller          ###   ########.fr       */
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
void    plane_intersect(t_object *pl, t_ray *ray, t_intersections *intersection)
{
    t_vector		o_p;
    double			numerator;
    double			denominator;
    double			t;
    double**		inverse_transform;
    t_ray			object_space_ray;
    t_vector		transformed_normal;

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
    // Free the inverse transformation matrix
    free_matrix(inverse_transform);
}
