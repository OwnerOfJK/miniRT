/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 20:25:49 by ecarlier          #+#    #+#             */
/*   Updated: 2024/06/21 13:39:09 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

int	color_at_intersection(t_intersections *intersection,
	t_data *data, t_ray *ray)
{
	bool		in_shadow;
	t_vector	normal_vector;
	int			color;

	normal_vector = normal_at(intersection, ray);
	in_shadow = shadow_at_intersection(data, intersection->intersection_point);
	color = calculate_lighting(data, intersection->intersection_point,
			normal_vector, intersection->color, in_shadow);
	return (color);
}

int	set_color(t_data *data, int x, int y)
{
	double			viewport_x;
	double			viewport_y;
	t_ray			*ray;
	t_intersections	*intersection;
	int				color;

	viewport_x = 0;
	viewport_y = 0;
	viewport_x = pixel_map_x(x, data->viewport);
	viewport_y = pixel_map_y(y, data->viewport);
	ray = prepare_ray(data, viewport_x, viewport_y);
	color = BACKGROUND;
	intersection = object_intersection(data->input->objects, ray);
	if (intersection)
	{
		if (intersection->hit == 1)
			color = color_at_intersection(intersection, data, ray);
	}
	else
		color = BACKGROUND;
	return (color);
}

void	render(t_data *data)
{
	int				x;
	int				y;
	int				color;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			color = set_color(data, x, y);
			my_mlx_pixel_put(&data->display, x, y, color);
		}
	}
	mlx_put_image_to_window(data->display.mlx_ptr,
		data->display.win_ptr, data->display.img, 0, 0);
}
