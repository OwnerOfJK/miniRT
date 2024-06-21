/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 20:43:09 by jkaller           #+#    #+#             */
/*   Updated: 2024/06/21 12:21:48 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

/*
Computes a colour in format trgb for mlx library
*/
t_color_mlx	rgb_to_colour(t_color rgb)
{
	return (*(int *)(unsigned char [4]){rgb.b, rgb.g, rgb.r, 255});
}


// t_intersections	shape_intersection(t_plane *pl, t_sphere *sp, t_ray *ray)
// {
// 	t_intersections	pl_inter;
// 	t_intersections	sp_inter;
// 	t_intersections	closest;

// 	pl_inter = plane_inter(pl, ray);
// 	sp_inter = spheres_inter(sp, ray);
// 	return (sp_inter);
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

t_intersections	shape_intersection(t_plane *pl, t_sphere *sp, t_ray *ray)
{
	t_intersections	pl_inter;
	t_intersections	sp_inter;
	t_intersections	closest;

	pl_inter = plane_inter(pl, ray);
	sp_inter = spheres_inter(sp, ray);

	if (pl_inter.t1 < sp_inter.t1)
		closest = pl_inter;
	else
		closest = sp_inter;
	return (closest);
}

// t_plane	*create_plane(t_vector pos, t_vector normal_vector, t_color color)
// {
// 	t_plane	*plane;

// 	plane->pos = pos;
// 	plane->normal_vector = normal_vector;
// 	plane->color = color;

// 	return (plane);
// }
//t_vector	ray_at()
