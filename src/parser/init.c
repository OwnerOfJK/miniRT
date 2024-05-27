/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:33:24 by ecarlier          #+#    #+#             */
/*   Updated: 2024/05/27 20:51:03 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../../include/miniRT.h"

// t_ray	*init_ray(void)
// {
// 	t_ray	*ray;

// 	ray = malloc(sizeof(t_ray));
// 	ray->origin = malloc(sizeof(t_vector));
// 	ray->direction = malloc(sizeof(t_vector));
// 	return (ray);
// }

void	launching_mlx(t_data *data)
{
	//launchviewport
	data->display.mlx_ptr = mlx_init();
	if (!data->display.mlx_ptr)
		error_free(data, "Error malloc mlx ");
	data->display.win_ptr = mlx_new_window(data->display.mlx_ptr, WIDTH, HEIGHT, "miniRT");
	if (!data->display.win_ptr)
		error_free(data, "Error malloc mlx window");
	data->display.img = mlx_new_image(data->display.mlx_ptr, WIDTH, HEIGHT);
	if (!data->display.img)
		error_free(data, "Error malloc mlx image");
	data->display.addr = mlx_get_data_addr(data->display.img, &data->display.bpp, \
		&data->display.line_length, &data->display.endian);
	if (!data->display.addr)
		error_free(data, "Error malloc mlx address");

	//mlx_hook(data->display.win_ptr, DestroyNotify, StructureNotifyMask, quit, world);
	render_scene(data);
	event_init(data);
	mlx_loop(data->display.mlx_ptr);

}

void	event_init(t_data *data)
{
	mlx_hook(data->display.win_ptr, 02, (1L << 0), key_handler, data);
	//mlx_hook(data->display.win_ptr, 04, (1L << 2), mouse_handler, data);
	mlx_hook(data->display.win_ptr, 17, (1L << 17), clean_exit, data);

}

int	key_handler(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		clean_exit(data);
	printf("The %d key has been pressed\n\n", keysym);
	render_scene(data);
	return (0);
}
