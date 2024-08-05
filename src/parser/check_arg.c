/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 19:01:57 by ecarlier          #+#    #+#             */
/*   Updated: 2024/08/05 19:41:19 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

bool static	check_rgb(t_input *input)
{
	t_object	*current;

	current = input->objects;
	while (current != NULL)
	{
		if (current->color.r < 0 || current->color.r > 255
			|| current->color.g < 0 || current->color.g > 255
			|| current->color.b < 0 || current->color.b > 255)
			return (true);
		current = current->next;
	}
	return (false);
}

bool static	check_ambient_light(t_input *input)
{
	t_alight	*alight;

	alight = input->alight;
	if (alight->ratio < 0 || alight->ratio > 1)
		return (true);
	if (alight->color.r < 0 || alight->color.r > 255
		|| alight->color.g < 0 || alight->color.g > 255
		|| alight->color.b < 0 || alight->color.b > 255)
		return (true);
	else
		return (false);
}

bool	static	check_fov_cam(t_input *input)
{
	t_camera	*camera;

	camera = input->camera;
	if (camera->fov < 0 || camera->fov > 180)
		return (true);
	else
		return (false);
}

bool	static	check_bright_light(t_input *input)
{
	t_light	*light;

	light = input->light;
	if (light->brightness < 0 || light->brightness > 1)
		return (true);
	else
		return (false);
}

void	check_arg(t_data *data, t_input *input)
{
	if (check_rgb(input))
		error_free_data(data, "Error: R,G,B colors not in range [0-255].\n");
	if (check_ambient_light(input))
		error_free_data(data,
			"Error: ambient lighting ratio not in range [0.0,1.0] \n");
	if (check_fov_cam(input))
		error_free_data(data, "Error: fov not in range [0,180]\n");
	if (check_bright_light(input))
		error_free_data(data,
			"Error: light brightness ratio not in range [0.0,1.0]\n");
}
