/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 11:53:27 by jkaller           #+#    #+#             */
/*   Updated: 2024/07/09 15:44:54 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

double	set_diffuse(t_data *data, t_vector normal, t_intersections *intersect)
{
	t_vector	light_direction;
	t_vector	view_direction;
	double		diffuse;

	light_direction = v_normalize(v_sub(data->input->light->pos,
				intersect->intersection_point));
	view_direction = v_normalize(v_sub(data->input->camera->pos,
				intersect->intersection_point));
	diffuse = fmax(0, v_dot(normal, light_direction))
						* data->input->material->diffuse
						* data->input->light->brightness;
	return (diffuse);
}

double	set_specular(t_data *data, t_vector normal, t_intersections *intersect)
{
	t_vector	reflection;
	double		dot_product;
	double		specular;
	t_vector	light_direction;
	t_vector	view_direction;

	light_direction = v_normalize(v_sub(data->input->light->pos,
				intersect->intersection_point));
	view_direction = v_normalize(v_sub(data->input->camera->pos,
				intersect->intersection_point));
	reflection = l_reflect(light_direction, normal);
	dot_product = v_dot(view_direction, reflection);
	specular = pow(fmax(0, dot_product), data->input->material->shininess)
		* data->input->material->specular * data->input->light->brightness;
	return (specular);
}

t_vector	l_reflect(t_vector light_in, t_vector normal_vector)
{
	double		dot_product;
	t_vector	scaled_normal;

	dot_product = v_dot(light_in, normal_vector);
	scaled_normal = v_scalar(normal_vector, 2 * dot_product);
	return (v_sub(light_in, scaled_normal));
}

int	calculate_lighting(t_data *data, t_intersections *intersection,
	t_vector normal, bool in_shadow)
{
	t_color		final_color;
	double		diffuse;
	double		specular;

	diffuse = set_diffuse(data, normal, intersection);
	specular = set_specular(data, normal, intersection);
	final_color.r = data->input->alightning->ratio
		* data->input->alightning->color.r / 255;
	final_color.g = data->input->alightning->ratio
		* data->input->alightning->color.g / 255;
	final_color.b = data->input->alightning->ratio
		* data->input->alightning->color.b / 255;
	if (in_shadow)
	{
		diffuse = 0;
		specular = 0;
	}
	final_color.r = fmin(1.0, fmax(0.0, (final_color.r
					+ diffuse + specular) * intersection->color.r / 255));
	final_color.g = fmin(1.0, fmax(0.0, (final_color.g
					+ diffuse + specular) * intersection->color.g / 255));
	final_color.b = fmin(1.0, fmax(0.0, (final_color.b
					+ diffuse + specular) * intersection->color.b / 255));
	return (rgb_to_colour(final_color));
}
