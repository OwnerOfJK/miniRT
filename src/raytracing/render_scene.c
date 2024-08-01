/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 20:25:49 by ecarlier          #+#    #+#             */
/*   Updated: 2024/08/01 18:47:18 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void print_objects(t_object *objects)
{
    int count = 0;
    while (objects != NULL)
    {
        printf("\nObject %d:\n", ++count);
        printf("Type: ");
        switch(objects->type)
        {
            case SPHERE:
                printf("Sphere\n");
                printf("Position: (%.2f, %.2f, %.2f)\n", objects->pos.x, objects->pos.y, objects->pos.z);
                printf("Diameter: %.2f\n", objects->shape.sphere.diameter);
                break;
            case PLANE:
                printf("Plane\n");
                printf("Position: (%.2f, %.2f, %.2f)\n", objects->pos.x, objects->pos.y, objects->pos.z);
                printf("Normal: (%.2f, %.2f, %.2f)\n", objects->shape.plane.normal_vector.x, 
                       objects->shape.plane.normal_vector.y, objects->shape.plane.normal_vector.z);
                break;
            case CYLINDER:
                printf("Cylinder\n");
                printf("Position: (%.2f, %.2f, %.2f)\n", objects->pos.x, objects->pos.y, objects->pos.z);
                printf("Axis: (%.2f, %.2f, %.2f)\n", objects->shape.cylinder.axis_vector.x, 
                       objects->shape.cylinder.axis_vector.y, objects->shape.cylinder.axis_vector.z);
                printf("Diameter: %.2f\n", objects->shape.cylinder.diameter);
                printf("Height: %.2f\n", objects->shape.cylinder.height);
                break;
            default:
                printf("Unknown\n");
        }
        
        // Print a few elements of the transformation matrix as a sanity check
        printf("Transformation Matrix (first 2x2):\n");
        printf("%.2f %.2f\n", objects->transformation_matrix[0][0], objects->transformation_matrix[0][1]);
        printf("%.2f %.2f\n", objects->transformation_matrix[1][0], objects->transformation_matrix[1][1]);
        
        objects = objects->next;
    }
    printf("\nTotal objects: %d\n", count);
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

int	set_color(t_data *data, int x, int y, t_ray *ray,
	t_intersections *intersection)
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
	intersection = (t_intersections *)ft_calloc(sizeof(t_intersections), 1);
	print_objects(data->input->objects);
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			color = set_color(data, x, y, ray, intersection);
			my_mlx_pixel_put(&data->display, x, y, color);
			if ((y * WIDTH + x) % (WIDTH * HEIGHT / 20) == 0)
				ft_printf("Rendering progress: %d%%\n",
					((y * WIDTH + x) * 100) / (WIDTH * HEIGHT));
		}
	}
	mlx_put_image_to_window(data->display.mlx_ptr,
		data->display.win_ptr, data->display.img, 0, 0);
	free(intersection);
	free(ray);
}
