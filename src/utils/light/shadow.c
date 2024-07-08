/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 12:14:44 by jkaller           #+#    #+#             */
/*   Updated: 2024/06/21 14:21:16 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

bool	is_shadowed(t_data *data, t_vector point)
{
	double			distance;
	t_vector		direction;
	t_ray			*shadow_ray;
	t_intersections	*intersections;
	double			t;

	distance = v_length(v_sub(data->input->light->pos, point));
	direction = v_normalize(v_sub(data->input->light->pos, point));
	shadow_ray = ray_init(point, direction);
	intersections = object_intersection(data->input->objects, shadow_ray);
	if (!intersections)
		return (false);
	t = intersections->t1;
	if (t > 0 && t < distance)
		return (true);
	return (false);
}

bool	shadow_at_intersection(t_data *data, t_vector intersection_point)
{
	bool		in_shadow;
	t_vector	camera_direction;
	t_vector	adjusted_point;

	camera_direction = v_sub(data->input->camera->pos, intersection_point);
	camera_direction = v_normalize(camera_direction);
	adjusted_point = v_add(intersection_point,
			v_scalar(camera_direction, EPSILON));
	in_shadow = is_shadowed(data, adjusted_point);
	return (in_shadow);
}
