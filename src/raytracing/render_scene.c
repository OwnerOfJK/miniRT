/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 20:25:49 by ecarlier          #+#    #+#             */
/*   Updated: 2024/06/17 16:11:25 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

// Initializes the window and starts the rendering process
void	launch_window(t_data *data)
{
	launch_mlx(data);  // Initialize mlx and create the window
	data->input->sphere->transformation_matrix = m_translate(data->input->sphere->pos);
	data->viewport = viewport_init(data->input->camera);  // Initialize the viewport
	data->input->sphere->material = material_init();
	render(data);  // Render the scene
	event_init(data);  // Initialize event handling
	mlx_loop(data->display.mlx_ptr);  // Enter the mlx event loop
}

// Initializes the mlx library and creates a new window and image for rendering
void    launch_mlx(t_data *data)
{
	data->display.mlx_ptr = mlx_init();
	if (!data->display.mlx_ptr)
		error_free(data, "Error malloc mlx ");
	data->display.win_ptr = mlx_new_window(data->display.mlx_ptr, WIDTH, HEIGHT, "miniRT");
	if (!data->display.win_ptr)
		error_free(data, "Error malloc mlx window");
	data->display.img = mlx_new_image(data->display.mlx_ptr, WIDTH, HEIGHT);
	if (!data->display.img)
		error_free(data, "Error malloc mlx image");
	data->display.addr = mlx_get_data_addr(data->display.img, &data->display.bpp, \
		&data->display.line_length, &data->display.endian);
	if (!data->display.addr)
		error_free(data, "Error malloc mlx address");
}

// Renders the scene by casting rays for each pixel and checking for intersections with the sphere
void	render(t_data *data)
{
	int				x;
	int				y;
	int				color;
	double			viewport_x;
	double			viewport_y;
	t_ray			*ray;
	t_intersections	intersections;

	viewport_x = 0;
	viewport_y = 0;
	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			// Map the pixel coordinates to the viewport coordinates
			viewport_x = pixel_map_x(x, data->viewport);
			viewport_y = pixel_map_y(y, data->viewport);
			// Prepare the ray for the current pixel
			ray = prepare_ray(data, viewport_x, viewport_y);
			// Check for intersections with the sphere
			//intersections = sphere_intersections(data->input->sphere, ray);
			intersections = shape_intersection(data->input->plane, data->input->sphere, ray);
			// Set the pixel color based on whether there was an intersection
			if (intersections.hit == 1)
			{
				double t = intersections.t1;
				t_vector intersection_point = ray_position(ray, t);
        		t_vector normal = normal_at(data->input->sphere, intersection_point);
				color = calculate_lighting(data, intersection_point, normal, intersections.color);
			}
			else
				color = 0x66FFB2;  // White for miss
			my_mlx_pixel_put(&data->display, x, y, color);
		}
	}
	// Display the rendered image in the window
	mlx_put_image_to_window(data->display.mlx_ptr, data->display.win_ptr, data->display.img, 0, 0);
}


void	my_mlx_pixel_put(t_graphics *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}