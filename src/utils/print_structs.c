/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_structs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 23:13:40 by jkaller           #+#    #+#             */
/*   Updated: 2024/06/03 14:44:42 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	print_double_pointer(char **double_pointer)
{
	int	i;

	i = 0;
	while (double_pointer[i] != NULL)
	{
		ft_printf("%s\n", double_pointer[i]);
		i++;
	}
}

void	print_camera(t_camera *camera)
{
	printf("Camera\n");
	printf("Position: %f %f %f\n", camera->pos->x, camera->pos->y, camera->pos->z);
	printf("Direction: %f %f %f\n", camera->orientation_vector->x, camera->orientation_vector->y, camera->orientation_vector->z);
	printf("FOV: %f\n", camera->fov);
	printf("\n");
}

void	print_alightning(t_alightning *alightning)
{
	printf("Ambient lightning\n");
	printf("Ratio: %f\n", alightning->ratio);
	printf("Color: %f %f %f\n", alightning->color->r, alightning->color->g, alightning->color->b);
	printf("\n");
}

void	print_light(t_light *light)
{
	printf("Light\n");
	printf("Position: %f %f %f\n", light->pos->x, light->pos->y, light->pos->z);
	printf("Brightness: %f\n", light->brightness);
	printf("\n");
}

void	print_sphere(t_sphere *sphere)
{
	while (sphere != NULL)
	{
		printf("Sphere\n");
		printf("Position: %f %f %f\n", sphere->pos->x, sphere->pos->y, sphere->pos->z);
		printf("Diameter: %f\n", sphere->diameter);
		printf("Color: %f %f %f\n", sphere->color->r, sphere->color->g, sphere->color->b);
		sphere = (t_sphere *)sphere->base.next;
	}
	printf("\n");
}

void	print_plane(t_plane *plane)
{
	while (plane != NULL)
	{
		printf("Plane\n");
		printf("Position: %f %f %f\n", plane->pos->x, plane->pos->y, plane->pos->z);
		printf("Normal vector: %f %f %f\n", plane->normal_vector->x, plane->normal_vector->y, plane->normal_vector->z);
		printf("Color: %f %f %f\n", plane->color->r, plane->color->g, plane->color->b);
		plane = (t_plane *)plane->base.next;
	}
	printf("\n");
}

void	print_cylinder(t_cylinder *cylinder)
{
	while (cylinder != NULL)
	{
		printf("Cylinder\n");
		printf("Position: %f %f %f\n", cylinder->pos->x, cylinder->pos->y, cylinder->pos->z);
		printf("Normal vector: %f %f %f\n", cylinder->axis_vector->x, cylinder->axis_vector->y, cylinder->axis_vector->z);
		printf("Diameter: %f\n", cylinder->diameter);
		printf("Height: %f\n", cylinder->height);
		printf("Color: %f %f %f\n", cylinder->color->r, cylinder->color->g, cylinder->color->b);
		cylinder = (t_cylinder *)cylinder->base.next;
	}
	printf("\n");
}

void	print_input(t_input *input)
{
	print_alightning(input->alightning);
	print_camera(input->camera);
	print_light(input->light);
	print_sphere(input->sphere);
	print_plane(input->plane);
	print_cylinder(input->cylinder);
}

