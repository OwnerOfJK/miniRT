/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 21:33:00 by jkaller           #+#    #+#             */
/*   Updated: 2024/06/16 21:34:18 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

// Initializes the viewport based on the camera's field of view
t_viewport	*viewport_init(t_camera *camera)
{
	t_viewport	*viewport;

	viewport = malloc(sizeof(t_viewport));
	viewport->fov_radians = camera->fov * (PI / 180);  // Convert FOV to radians
	viewport->viewport_height = 2 * tan(viewport->fov_radians / 2);  // Calculate viewport height
	viewport->viewport_width = viewport->viewport_height; // Because aspect ratio is 1 (i.e 800:800)
	return (viewport);
}

t_material	material_init(void)
{
	t_material	material;

	material.ambient = 0.1;
	material.diffuse = 0.9;
	material.specular = 0.9;
	material.shininess = 200;
	return (material);
}
