/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 19:44:10 by ecarlier          #+#    #+#             */
/*   Updated: 2024/07/31 20:46:09 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

/*
Maps the x coordinate of a pixel to the corresponding x coordinate
 on the viewport
*/

double	pixel_map_x(int x, t_viewport *viewport)
{
	double	normalized_x;
	double	viewport_x;

	normalized_x = (x + 0.5) / WIDTH * 2 - 1;
	viewport_x = normalized_x * (viewport->viewport_width / 2);
	return (viewport_x);
}

double	pixel_map_y(int y, t_viewport *viewport)
{
	double	normalized_y;
	double	viewport_y;

	normalized_y = 1 - (y + 0.5) / HEIGHT * 2;
	viewport_y = normalized_y * (viewport->viewport_height / 2);
	return (viewport_y);
}

/*
Prepares a ray from the camera origin through the specified viewport coordinates
*/
void	prepare_ray(t_data *data, double viewport_x,
	double viewport_y, t_ray *ray)
{
	ray->origin = data->input->camera->pos;
	ray->direction.x = viewport_x;
	ray->direction.y = viewport_y;
	ray->direction.z = 1;
	ray->direction.w = 0;
	ray->direction = v_normalize(ray->direction);
}
