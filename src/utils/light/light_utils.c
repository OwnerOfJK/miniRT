/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 16:23:05 by jkaller           #+#    #+#             */
/*   Updated: 2024/06/20 16:14:51 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

t_vector normal_at(t_object *object, t_vector world_point)
{
    t_vector normal;

    normal = v_init(0, 0, 0, 0);
    if (object->type == SPHERE) {
        double** inverse_transform = m_inverse(object->transformation_matrix);
        t_vector object_point = mv_mult(inverse_transform, world_point);
        normal = v_sub(object_point, v_init(0, 0, 0, 1));
        normal = v_normalize(normal);
        t_vector world_normal = mv_mult(m_transpose(inverse_transform), normal);
        normal = v_normalize(world_normal);
        free_matrix(inverse_transform);
    } else if (object->type == PLANE) {
        double** inverse_transform = m_inverse(object->transformation_matrix);
        t_vector transformed_normal = mv_mult(m_transpose(inverse_transform), object->shape.plane.normal_vector);
        normal = v_normalize(transformed_normal);
        free_matrix(inverse_transform);
    } else if (object->type == CYLINDER) {
        double **inverse_transform = m_inverse(object->transformation_matrix);
        t_vector object_point = mv_mult(inverse_transform, world_point);

        // Assume cylinder is aligned along the z-axis in object space
        t_vector cylinder_base_to_point = v_sub(object_point, v_init(0, 0, object_point.z, 1));
        normal = v_normalize(cylinder_base_to_point);

        t_vector world_normal = mv_mult(m_transpose(inverse_transform), normal);
        normal = v_normalize(world_normal);
        free_matrix(inverse_transform);
    }
    return normal;
}

t_vector l_reflect(t_vector light_in, t_vector normal_vector)
{
    double dot_product = v_dot(light_in, normal_vector);
    t_vector scaled_normal = v_scalar(normal_vector, 2 * dot_product);
    return v_sub(light_in, scaled_normal);
}

int calculate_lighting(t_data *data, t_vector intersection_point, t_vector normal, t_color base_color) {
    t_vector light_pos = data->input->light->pos;
    double brightness = data->input->light->brightness;
    
    t_vector light_direction = v_sub(light_pos, intersection_point);
    light_direction = v_normalize(light_direction);
    
    // Ambient light contribution
    double ambient = data->input->material->ambient;
    
    // Diffuse light contribution
    double diffuse = fmax(0, v_dot(normal, light_direction)) * data->input->material->diffuse * brightness;
    
    // Specular light contribution
    t_vector view_direction = v_sub(data->input->camera->pos, intersection_point);
    view_direction = v_normalize(view_direction);
    t_vector reflection_direction = l_reflect(light_direction, normal);
    double specular = pow(fmax(0, v_dot(view_direction, reflection_direction)), data->input->material->shininess) * data->input->material->specular * brightness;
    
    double final_red = (ambient + diffuse + specular) * base_color.r / 255;
    double final_green = (ambient + diffuse + specular) * base_color.g / 255;
    double final_blue = (ambient + diffuse + specular) * base_color.b / 255;
    
    // Ensure color values are within valid range
    final_red = fmin(1.0, fmax(0.0, final_red));
    final_green = fmin(1.0, fmax(0.0, final_green));
    final_blue = fmin(1.0, fmax(0.0, final_blue));
    
    t_color_mlx color = rgb_to_colour((t_color){final_red * 255, final_green * 255, final_blue * 255});
    
    return color;
}
