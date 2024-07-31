/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 12:14:44 by jkaller           #+#    #+#             */
/*   Updated: 2024/07/31 18:23:44 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

bool	is_shadowed(t_data *data, t_vector point, t_ray *ray)
{
	double			distance;
	t_vector		direction;
	t_intersections	*shadow_intersection;
	double			t;

	distance = v_length(v_sub(data->input->light->pos, point));
	direction = v_normalize(v_sub(data->input->light->pos, point));
	ray->origin = point;
	ray->direction = direction;

	shadow_intersection = (t_intersections *)malloc(sizeof(t_intersections));
	shadow_intersection->t1 = DBL_MAX;
	shadow_intersection->count = 0;
	shadow_intersection->hit = 0;

	object_intersection(data->input->objects, ray, shadow_intersection);
	if (!shadow_intersection->hit)
		return (false);

	t = shadow_intersection->t1;
	free(shadow_intersection);
	if (t > 0 && t < distance)
		return (true);
	return (false);
}

bool	shadow_at_intersection(t_data *data, t_intersections *intersection,
	t_ray *ray)
{
	bool		in_shadow;
	t_vector	camera_direction;
	t_vector	adjusted_point;

	camera_direction = v_sub(data->input->camera->pos,
			intersection->intersection_point);
	camera_direction = v_normalize(camera_direction);
	adjusted_point = v_add(intersection->intersection_point,
			v_scalar(camera_direction, EPSILON));
	in_shadow = is_shadowed(data, adjusted_point, ray);
	return (in_shadow);
}
