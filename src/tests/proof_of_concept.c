/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proof_of_concept.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 13:41:33 by jkaller           #+#    #+#             */
/*   Updated: 2024/06/15 17:24:35 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

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
			intersections = sphere_intersections(data->input->sphere, ray);
			// Set the pixel color based on whether there was an intersection
			if (intersections.count == 2 || intersections.count == 1)
				color = 0x00FF00;  // Green for hit
			else
				color = 0x0000FF;  // Blue for miss
			my_mlx_pixel_put(&data->display, x, y, color);
		}
	}
	// Display the rendered image in the window
	mlx_put_image_to_window(data->display.mlx_ptr, data->display.win_ptr, data->display.img, 0, 0);
}

// Initializes the viewport based on the camera's field of view
t_viewport	*viewport_init(t_camera *camera)
{
	t_viewport	*viewport;

	viewport = malloc(sizeof(t_viewport));
	viewport->fov_radians = camera->fov * (PI / 180);  // Convert FOV to radians
	viewport->viewport_height = 2 * tan(viewport->fov_radians / 2);  // Calculate viewport height
	viewport->viewport_width = viewport->viewport_height; // Because aspect ratio is 1 (i.e 800:800)
	return (viewport);
}

// Initializes the window and starts the rendering process
void	launch_window(t_data *data)
{
	t_sphere	*sphere;
	t_camera	*camera;

	launch_mlx(data);  // Initialize mlx and create the window
	sphere = data->input->sphere;  // Get the sphere from the input data
	camera = data->input->camera;  // Get the camera from the input data
	data->viewport = viewport_init(camera);  // Initialize the viewport
	render(data);  // Render the scene
	event_init(data);  // Initialize event handling
	mlx_loop(data->display.mlx_ptr);  // Enter the mlx event loop
}

// Entry point for the proof of concept test
int	test_proof_of_concept(t_data *data)
{
	launch_window(data);  // Launch the window and render the scene
	printf("Proof Of Concept launched!\n");
	return (0);
}
