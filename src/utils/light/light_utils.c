/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 16:23:05 by jkaller           #+#    #+#             */
/*   Updated: 2024/06/16 20:55:11 by jkaller          ###   ########.fr       */
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
