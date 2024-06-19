/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_structs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 23:13:40 by jkaller           #+#    #+#             */
/*   Updated: 2024/06/19 15:21:49 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

// void	print_double_pointer(char **double_pointer)
// {
// 	int	i;

// 	i = 0;
// 	while (double_pointer[i] != NULL)
// 	{
// 		ft_printf("%s\n", double_pointer[i]);
// 		i++;
// 	}
// }

// Function to print t_vector
void print_vector(const char *name, t_vector vec) {
    printf("%s: {x: %f, y: %f, z: %f, w: %f}\n", name, vec.x, vec.y, vec.z, vec.w);
}

// Function to print t_color
void print_color(const char *name, t_color color) {
    printf("%s: {r: %f, g: %f, b: %f}\n", name, color.r, color.g, color.b);
}

// Function to print t_material
void print_material(const t_material *material) {
    printf("Material: {ambient: %f, diffuse: %f, specular: %f, shininess: %f}\n", 
           material->ambient, material->diffuse, material->specular, material->shininess);
}

// Function to print t_alightning
void print_alightning(const t_alightning *alight) {
    printf("Ambient Lighting: {ratio: %f, color: {r: %f, g: %f, b: %f}}\n", 
           alight->ratio, alight->color.r, alight->color.g, alight->color.b);
}

// Function to print t_camera
void print_camera(const t_camera *camera) {
    printf("Camera: \n");
    print_vector("  Position", camera->pos);
    print_vector("  Orientation", camera->orientation_vector);
    printf("  FOV: %f\n", camera->fov);
}

// Function to print t_light
void print_light(const t_light *light) {
    printf("Light: \n");
    print_vector("  Position", light->pos);
    printf("  Brightness: %f\n", light->brightness);
}

void print_input(const t_input *input)
{
    if (input->alightning) {
        print_alightning(input->alightning);
    } else {
        printf("Ambient Lighting: NULL\n");
    }

    if (input->camera) {
        print_camera(input->camera);
    } else {
        printf("Camera: NULL\n");
    }

    if (input->light) {
        print_light(input->light);
    } else {
        printf("Light: NULL\n");
    }

    printf("Objects:\n");
    t_object *obj = input->objects;
    while (obj != NULL) {
        switch (obj->type) {
            case SPHERE:
                printf("  Object Type: SPHERE\n");
                print_vector("  Position", obj->pos);
                print_color("  Color", obj->color);
                print_material(input->material);
                printf("  Diameter: %f\n", obj->shape.sphere.diameter);
                break;

            case PLANE:
                printf("  Object Type: PLANE\n");
                print_vector("  Position", obj->pos);
                print_color("  Color", obj->color);
                print_material(input->material);
                print_vector("  Normal Vector", obj->shape.plane.normal_vector);
                break;

            case CYLINDER:
                printf("  Object Type: CYLINDER\n");
                print_vector("  Position", obj->pos);
                print_color("  Color", obj->color);
                print_material(input->material);
                print_vector("  Axis Vector", obj->shape.cylinder.axis_vector);
                printf("  Diameter: %f\n", obj->shape.cylinder.diameter);
                printf("  Height: %f\n", obj->shape.cylinder.height);
                break;
        }
        obj = obj->next;
    }
}