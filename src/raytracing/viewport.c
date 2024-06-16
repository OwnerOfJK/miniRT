/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 19:44:10 by ecarlier          #+#    #+#             */
/*   Updated: 2024/06/16 21:51:56 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

// Maps the x coordinate of a pixel to the corresponding x coordinate on the viewport
double	pixel_map_x(int x, t_viewport *viewport)
{
	double	normalized_x;
	double	viewport_x;

	// Normalize the pixel x coordinate to the range [-1, 1]
	normalized_x = (x + 0.5) / WIDTH * 2 - 1;
	// Convert the normalized x coordinate to the viewport x coordinate
	viewport_x = normalized_x * (viewport->viewport_width / 2);
	return (viewport_x);
}

// Maps the y coordinate of a pixel to the corresponding y coordinate on the viewport
double	pixel_map_y(int y, t_viewport *viewport)
{
	double	normalized_y;
	double	viewport_y;

	// Normalize the pixel y coordinate to the range [-1, 1]
	normalized_y = 1 - (y + 0.5) / HEIGHT * 2;
	// Convert the normalized y coordinate to the viewport y coordinate
	viewport_y = normalized_y * (viewport->viewport_height / 2);
	return (viewport_y);
}

// Prepares a ray from the camera origin through the specified viewport coordinates
t_ray	*prepare_ray(t_data *data, double viewport_x, double viewport_y)
{
	t_ray		*ray;
	t_vector	origin;
	t_vector	direction;
	double		length;

	// Get the camera position as the origin of the ray
	origin = data->input->camera->pos;
	// Create a direction vector from the camera through the viewport coordinates
	direction = v_init(viewport_x, viewport_y, 1, 0);
	// Normalize the direction vector
	length = v_length(direction);
	direction = v_normalize(direction);
	// Initialize the ray with the origin and direction
	ray = ray_init(origin, direction);
	return (ray);
}
