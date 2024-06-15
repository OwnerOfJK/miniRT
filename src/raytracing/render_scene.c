/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 20:25:49 by ecarlier          #+#    #+#             */
/*   Updated: 2024/06/15 15:45:11 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

int	clostest(t_data *data, t_ray *ray, t_intersections *closest)
{
	t_intersections	tmp;

	//go through all the shapes and keep the smallest t

}

void	render_scene(t_data *data)
{
	int		x;
	int		y;
	int		color;
	//t_ray	*ray;

	color = 0x0000FF; //blue
	//ray = init_ray();
	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			// 1) get the ray sent from the camera
			//change the color using the hit function
			color += 0x00000F;
			my_mlx_pixel_put(&data->display, x, y, color);
		}
	}
	mlx_put_image_to_window(data->display.mlx_ptr, data->display.win_ptr, data->display.img, 0, 0);

}
void	my_mlx_pixel_put(t_graphics *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}
