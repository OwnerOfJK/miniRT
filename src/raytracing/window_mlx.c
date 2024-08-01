/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_mlx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 12:55:17 by jkaller           #+#    #+#             */
/*   Updated: 2024/08/01 20:51:21 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	launch_window(t_data *data)
{
	launch_mlx(data);
	render(data);
	event_init(data);
	mlx_loop(data->display.mlx_ptr);
}

void	launch_mlx(t_data *data)
{
	data->display.mlx_ptr = mlx_init();
	if (!data->display.mlx_ptr)
		error_free_data(data, "Error malloc mlx ");
	data->display.win_ptr = mlx_new_window(data->display.mlx_ptr,
			WIDTH, HEIGHT, "miniRT");
	if (!data->display.win_ptr)
		error_free_data(data, "Error malloc mlx window");
	data->display.img = mlx_new_image(data->display.mlx_ptr, WIDTH, HEIGHT);
	if (!data->display.img)
		error_free_data(data, "Error malloc mlx image");
	data->display.addr = mlx_get_data_addr(data->display.img,
			&data->display.bpp, &data->display.line_length,
			&data->display.endian);
	if (!data->display.addr)
		error_free_data(data, "Error malloc mlx address");
}

void	my_mlx_pixel_put(t_graphics *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}
