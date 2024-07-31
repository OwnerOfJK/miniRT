/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 23:20:40 by jkaller           #+#    #+#             */
/*   Updated: 2024/07/31 14:49:21 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	free_mlx(t_graphics display)
{
	mlx_destroy_image(display.mlx_ptr, display.img);
	mlx_destroy_window(display.mlx_ptr, display.win_ptr);
	mlx_destroy_display(display.mlx_ptr);
	free(display.mlx_ptr);
}

void	free_input(t_input *input)
{
	free(input->alight);
	free(input->camera);
	free(input->light);
	free_objects(input->objects);
	free(input->material);
	free(input);
}

void	free_objects(t_object *objects)
{
	t_object	*tmp;

	while (objects != NULL)
	{
		tmp = objects;
		objects = objects->next;
		if (tmp->transformation_matrix != NULL)
			free_matrix(tmp->transformation_matrix);
		if (tmp->inverse_matrix != NULL)
			free_matrix(tmp->inverse_matrix);
		free(tmp);
	}
}

void	free_data(t_data *data)
{
	free_mlx(data->display);
	free_input(data->input);
	free(data->viewport);
	free(data);
}
