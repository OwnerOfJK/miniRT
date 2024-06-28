/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 20:25:49 by ecarlier          #+#    #+#             */
/*   Updated: 2024/06/28 17:02:18 by ecarlier         ###   ########.fr       */
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
	color = calculate_lighting(data, intersection, normal_vector, in_shadow);
	return (color);
}

int	set_color(t_data *data, int x, int y)
{
	double			viewport_x;
	double			viewport_y;
	t_ray			*ray;
	t_intersections	*intersection;
	int				color;

	color = BACKGROUND;
	viewport_x = pixel_map_x(x, data->viewport);
	viewport_y = pixel_map_y(y, data->viewport);
	ray = prepare_ray(data, viewport_x, viewport_y);
	intersection = object_intersection(data->input->objects, ray);
	if (intersection)
	{
		if (intersection->hit == 1)
			color = color_at_intersection(intersection, data, ray);
	}
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
			if ((y * WIDTH + x) % (WIDTH * HEIGHT / 20) == 0)
				ft_printf("Rendering progress: %d%%\n", ((y * WIDTH + x) * 100) / (WIDTH * HEIGHT));
		}
	}
	mlx_put_image_to_window(data->display.mlx_ptr,
		data->display.win_ptr, data->display.img, 0, 0);
	ft_printf("Rendering done\n");
}
