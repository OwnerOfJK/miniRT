/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 23:59:01 by jkaller           #+#    #+#             */
/*   Updated: 2024/06/16 18:16:26 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

t_ray	*ray_init(t_vector origin, t_vector direction)
{
	t_ray	*ray;

	ray = malloc(sizeof(t_ray));
	if (!ray)
		return (NULL);
	ray->origin = origin;
	ray->direction = direction;
	return (ray);
}

t_vector	ray_position(t_ray *ray, double t)
{
	t_vector	position;

	position = v_add(ray->origin, v_scalar(ray->direction, t));
	return (position);
}

t_ray	ray_transform(t_ray *ray, double **matrix)
{
	t_ray	transformed_ray;

	transformed_ray.origin = mv_mult(matrix, ray->origin);
	transformed_ray.direction = mv_mult(matrix, ray->direction);
	return (transformed_ray);
}
