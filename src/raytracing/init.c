/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:20:05 by ecarlier          #+#    #+#             */
/*   Updated: 2024/06/15 15:32:52 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"


// t_ray	*init_ray(void)
// {
// 	(void()
// 	t_ray	*ray;

// 	ray = malloc(sizeof(t_ray));
// 	ray->direction = malloc(sizeof(t_vector));
// 	ray->origin = malloc(sizeof(t_vector));
// 	return (ray);
// }

// t_data	*create_world(t_data *world)
// {
// 	world = (t_data *)malloc(sizeof(t_data));
// 	world->input = input;

// 	//fake light to test
// 	world->light = (t_light *)malloc(sizeof(t_light));
// 	if (!world->light)
// 		return (NULL);
// 	world->light->pos = v_init(-10, 10, -10, 1);
// 	world->light->brightness = 1.0;


// 	world->sphere = input->sphere;
// 	world->plane = input->plane;
// 	world->cylinder = input->cylinder;
// 	world->camera = input->camera;


// 	printf("World created !\n");
// 	//ft_memset(data, 0, sizeof(t_data)); //delete later
// 	return (world);
// }
