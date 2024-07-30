/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:07:37 by jkaller           #+#    #+#             */
/*   Updated: 2024/07/30 17:22:46 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	free_alight(t_alight *alight)
{
	free(&(alight->color));
	free(alight);
}

void	free_camera(t_camera *camera)
{
	free(&(camera->pos));
	free(&(camera->orientation_vector));
	free(camera);
}

void	free_light(t_light *light)
{
	free(&(light->pos));
	free(light);
}

void	free_input(t_input *input)
{
	free_alight(input->alight);
	free_camera(input->camera);
	free_light(input->light);
	free_objects(input->objects);
	free(input->material);
	free(input);
}

