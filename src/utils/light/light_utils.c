/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 16:23:05 by jkaller           #+#    #+#             */
/*   Updated: 2024/06/16 21:29:47 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

t_vector normal_at(t_sphere *sp, t_vector world_point) {
    // Transform the world point to object space
    double** inverse_transform = m_inverse(sp->transformation_matrix);
    t_vector object_point = mv_mult(inverse_transform, world_point);
    
    // Compute the normal in object space
    t_vector object_normal = v_sub(object_point, v_init(0, 0, 0, 0));
    object_normal = v_normalize(object_normal);

    // Transform the normal back to world space
    t_vector world_normal = mv_mult(m_transpose(m_inverse(sp->transformation_matrix)), object_normal);
    world_normal = v_normalize(world_normal);  // Ensure the normal is normalized

    // Free the dynamically allocated inverse_transform matrix
    free_matrix(inverse_transform);
    return world_normal;
}

t_vector l_reflect(t_vector light_in, t_vector normal_vector)
{
    double dot_product = v_dot(light_in, normal_vector);
    t_vector scaled_normal = v_scalar(normal_vector, 2 * dot_product);
    return v_sub(light_in, scaled_normal);
}

int calculate_lighting(t_data *data, t_vector intersection_point, t_vector normal)
{
	t_vector	light_pos;
	double 		brightness;
	t_vector light_direction;

	light_pos = data->input->light->pos;
	brightness = data->input->light->brightness;
    // Direction from intersection point to the light source
    light_direction = v_sub(light_pos, intersection_point);
    light_direction = v_normalize(light_direction);

    // Ambient light contribution
    double ambient_coefficient = data->input->sphere->material.ambient;

    // Diffuse light contribution
    double diffuse_coefficient = data->input->sphere->material.diffuse;
    double diffuse_intensity = fmax(0, v_dot(normal, light_direction));

    // Specular light contribution
    double specular_coefficient = data->input->sphere->material.specular;
    t_vector view_direction = v_sub(data->input->camera->pos, intersection_point);
    view_direction = v_normalize(view_direction);
    t_vector reflection_direction = l_reflect(light_direction, normal);
    double specular_intensity = pow(fmax(0, v_dot(view_direction, reflection_direction)), data->input->sphere->material.shininess);

    // Combine ambient, diffuse, and specular components
    double r = ambient_coefficient + brightness * (diffuse_coefficient * diffuse_intensity + specular_coefficient * specular_intensity);
    double g = ambient_coefficient + brightness * (diffuse_coefficient * diffuse_intensity + specular_coefficient * specular_intensity);
    double b = ambient_coefficient + brightness * (diffuse_coefficient * diffuse_intensity + specular_coefficient * specular_intensity);

    // Ensure color values are within valid range
    r = fmin(1.0, fmax(0.0, r));
    g = fmin(1.0, fmax(0.0, g));
    b = fmin(1.0, fmax(0.0, b));

    // Convert to integer color representation
    int color = rgb_to_colour((t_color){r * 255, g * 255, b * 255});
	
    return (color);
}