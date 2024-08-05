/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 20:25:49 by ecarlier          #+#    #+#             */
/*   Updated: 2024/08/05 18:39:56 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	print_progress(t_coordinates coordinates)
{
	if ((coordinates.y * WIDTH + coordinates.x) % (WIDTH * HEIGHT / 20) == 0)
	{
		ft_printf("Rendering progress: %d%%\n",
			((coordinates.y * WIDTH + coordinates.x)
				* 100) / (WIDTH * HEIGHT));
	}
}

int	shading_at_intersection(t_intersections *intersection,
	t_data *data, t_ray *ray)
{
	bool		in_shadow;
	t_vector	normal_vector;
	int			color;

	in_shadow = false;
	normal_vector = normal_at(intersection, ray);
	in_shadow = shadow_at_intersection(data, intersection, ray);
	color = calculate_lighting(data, intersection, normal_vector, in_shadow);
	return (color);
}

int	set_color(t_data *data, t_coordinates coordinates, t_ray *ray,
	t_intersections *intersection)
{
	double			viewport_x;
	double			viewport_y;
	int				color;

	color = BACKGROUND;
	viewport_x = pixel_map_x(coordinates.x, data->input->viewport);
	viewport_y = pixel_map_y(coordinates.y, data->input->viewport);
	prepare_ray(data, viewport_x, viewport_y, ray);
	object_intersection(data->input->objects, ray, intersection);
	if (intersection)
	{
		if (intersection->hit == 1)
			color = shading_at_intersection(intersection, data, ray);
	}
	return (color);
}

void	render(t_data *data)
{
	int				color;
	t_coordinates	coordinates;
	t_ray			*ray;
	t_intersections	*intersection;

	coordinates.y = -1;
	ray = ray_init(v_init(0, 0, 0, 0), v_init(0, 0, 0, 0));
	intersection = (t_intersections *)ft_calloc(sizeof(t_intersections), 1);
	while (++coordinates.y < HEIGHT)
	{
		coordinates.x = -1;
		while (++coordinates.x < WIDTH)
		{
			color = set_color(data, coordinates, ray, intersection);
			my_mlx_pixel_put(&data->display, coordinates.x,
				coordinates.y, color);
			print_progress(coordinates);
		}
	}
	ft_printf("Rendering progress: 100%%\n");
	mlx_put_image_to_window(data->display.mlx_ptr,
		data->display.win_ptr, data->display.img, 0, 0);
	free(intersection);
	free(ray);
}
