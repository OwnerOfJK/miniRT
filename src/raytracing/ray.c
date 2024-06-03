/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 19:43:07 by ecarlier          #+#    #+#             */
/*   Updated: 2024/06/03 19:48:56 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"


/*
get the ray send from the camera, mimicking a viewport
(not a real one -> need to implement later)
*/
void	get_ray(t_ray *ray, t_data *data, int x, int y)
{
	t_vector	viewport; //fake
	double		scale;
	t_camera	*camera;

	camera = data->input->camera;

	scale = tan(radian(camera->fov) * 0.5);

	ray->origin = camera->pos; //origin of the camera




}
