/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 23:20:40 by jkaller           #+#    #+#             */
/*   Updated: 2024/07/30 17:23:46 by jkaller          ###   ########.fr       */
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

void	free_intersections(t_intersections *intersections)
{
	free(&(intersections->ray));
	free(&(intersections->color));
	free(&(intersections->intersection_point));
	free(&(intersections->normal));
	intersections->object = NULL;
	free(intersections);
}

void	free_data(t_data *data)
{
	free_mlx(data->display);
	free_intersections(data->intersections);
	free_input(data->input);
	free(data->viewport);
	free(data);
}