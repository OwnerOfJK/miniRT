/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 21:33:00 by jkaller           #+#    #+#             */
/*   Updated: 2024/08/01 22:26:36 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

t_data	*data_init(char **argv)
{
	t_data	*data;

	data = ft_calloc(sizeof(t_data), 1);
	if (data == NULL)
		error_free_nothing("Error: Memory allocation failed.\n");
	data->input = parse_input(data, argv[1]);
	if (data->input == NULL)
		error_free_data(data, "Error: Parsing failed.\n");
	return (data);
}

t_viewport	*viewport_init(t_data *data, t_camera *camera)
{
	t_viewport	*viewport;

	viewport = malloc(sizeof(t_viewport));
	if (viewport == NULL)
		error_free_data(data, "Error: Memory allocation failed.\n");
	viewport->fov_radians = camera->fov * (PI / 180);
	viewport->viewport_height = 2 * tan(viewport->fov_radians / 2);
	viewport->viewport_width = viewport->viewport_height;
	return (viewport);
}

t_material	*material_init(t_data *data)
{
	t_material	*material;

	material = malloc(sizeof(t_material));
	if (material == NULL)
		error_free_data(data, "Error: Memory allocation failed.\n");
	material->diffuse = 0.9;
	material->specular = 0.9;
	material->shininess = 200;
	return (material);
}

void	event_init(t_data *data)
{
	mlx_hook(data->display.win_ptr, 02, (1L << 0), key_handler, data);
	mlx_hook(data->display.win_ptr, 17, (1L << 17), clean_exit, data);
}

int	key_handler(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		clean_exit(data);
	printf("The %d key has been pressed\n\n", keysym);
	return (0);
}
