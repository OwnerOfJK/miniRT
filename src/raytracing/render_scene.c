/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 20:25:49 by ecarlier          #+#    #+#             */
/*   Updated: 2024/07/30 18:10:41 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

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

int	set_color(t_data *data, int x, int y, t_ray *ray, t_intersections *intersection)
{
	double			viewport_x;
	double			viewport_y;
	int				color;

	color = BACKGROUND;
	viewport_x = pixel_map_x(x, data->viewport);
	viewport_y = pixel_map_y(y, data->viewport);
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
	int				x;
	int				y;
	int				color;
	t_ray			*ray;
	t_intersections	*intersection;

	y = -1;
	ray = ray_init(v_init(0, 0, 0, 0), v_init(0, 0, 0, 0));
	intersection = (t_intersections *)malloc(sizeof(t_intersections));
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			color = set_color(data, x, y, ray, intersection);
			my_mlx_pixel_put(&data->display, x, y, color);
			if ((y * WIDTH + x) % (WIDTH * HEIGHT / 20) == 0)
				ft_printf("Rendering progress: %d%%\n", ((y * WIDTH + x) * 100) / (WIDTH * HEIGHT));
		}
	}
	mlx_put_image_to_window(data->display.mlx_ptr,
		data->display.win_ptr, data->display.img, 0, 0);
	free(intersection);
	free(ray);
	ft_printf("Rendering done\n");
}
