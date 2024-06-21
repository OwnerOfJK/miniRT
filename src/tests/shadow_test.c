/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 16:29:34 by jkaller           #+#    #+#             */
/*   Updated: 2024/06/21 13:20:22 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../include/miniRT.h"

// int test_calculate_lighting(t_vector intersection_point, t_vector normal, t_color base_color, bool in_shadow) {
//     t_vector light_pos = v_init(0, 0, -10, 1);
//     t_vector camera_pos = v_init(0, 0, 0, 1);
//     double brightness = 1;
    
//     t_vector light_direction = v_sub(light_pos, intersection_point);
//     light_direction = v_normalize(light_direction);
    
//     // Ambient light contribution
//     double ambient = 0.1;
    
//     // Diffuse light contribution
//     double diffuse = fmax(0, v_dot(normal, light_direction)) * 0.9 * brightness;
    
//     // Specular light contribution
//     t_vector view_direction = v_sub(camera_pos, intersection_point);
//     view_direction = v_normalize(view_direction);
//     t_vector reflection_direction = l_reflect(light_direction, normal);
//     double specular = pow(fmax(0, v_dot(view_direction, reflection_direction)), 200) * 0.9 * brightness;
    
//     printf("Ambient: %f\n", ambient);
//     printf("Diffuse: %f\n", diffuse);
//     printf("Specular: %f\n", specular);
//     if (in_shadow == true)
//     {
//         diffuse = 0;
//         specular = 0;
//     }
//     double final_red = (ambient + diffuse + specular) * base_color.r / 255;
//     double final_green = (ambient + diffuse + specular) * base_color.g / 255;
//     double final_blue = (ambient + diffuse + specular) * base_color.b / 255;
    
//     // Ensure color values are within valid range
//     final_red = fmin(1.0, fmax(0.0, final_red));
//     final_green = fmin(1.0, fmax(0.0, final_green));
//     final_blue = fmin(1.0, fmax(0.0, final_blue));
//     color_print((t_color){final_red * 255, final_green * 255, final_blue * 255});
//     t_color_mlx color = rgb_to_colour((t_color){final_red * 255, final_green * 255, final_blue * 255});
    
//     return color;
// }

// void	test_render(t_data *data)
// {
// 	int				x;
// 	int				y;
// 	int				color;
// 	double			viewport_x;
// 	double			viewport_y;
// 	t_ray			*ray;
// 	t_intersections	*intersections;
// 	bool			in_shadow;

// 	viewport_x = 0;
// 	viewport_y = 0;
// 	y = -1;
// 	in_shadow = true;
// 	while (++y < HEIGHT)
// 	{
// 		x = -1;
// 		while (++x < WIDTH)
// 		{
// 			// Map the pixel coordinates to the viewport coordinates
// 			viewport_x = pixel_map_x(x, data->viewport);
// 			viewport_y = pixel_map_y(y, data->viewport);
// 			// Prepare the ray for the current pixel
// 			ray = prepare_ray(data, viewport_x, viewport_y);
// 			// Check for intersections with the sphere
// 			//intersections = sphere_intersections(data->input->sphere, ray);
// 			intersections = object_intersection(data->input->objects, ray);
// 			// Set the pixel color based on whether there was an intersection
// 			if (intersections->hit == 1)
// 			{
// 				double t = intersections->t1;
// 				t_vector intersection_point = ray_position(ray, t);
//         		t_vector normal = normal_at(intersections->object, intersection_point);
// 				in_shadow = false;
// 				color = calculate_lighting(data, intersection_point, normal, intersections->color, in_shadow);
// 			}
// 			else
// 				color = 0x606060;  // for miss
// 			my_mlx_pixel_put(&data->display, x, y, color);
// 		}
// 	}
// 	// Display the rendered image in the window
// 	mlx_put_image_to_window(data->display.mlx_ptr, data->display.win_ptr, data->display.img, 0, 0);
// }

// void    test_shadows()
// {
//     t_vector    intersection_point = v_init(0, 0, 0, 1);
//     t_vector    normal = v_init(0, 0, 1, 0);
//     t_color     base_color = (t_color){255, 255, 255};
//     bool        in_shadow = true;

//     int color = test_calculate_lighting(intersection_point, normal, base_color, in_shadow);
//     printf("Color: %d\n", color);
// }