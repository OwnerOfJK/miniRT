/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:20:05 by ecarlier          #+#    #+#             */
/*   Updated: 2024/06/15 14:30:11 by ecarlier         ###   ########.fr       */
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

t_data	*create_world(t_data *world)
{
	world = (t_data *)malloc(sizeof(t_data));
	//ft_memset(data, 0, sizeof(t_data)); //delete later
	return (world);
}
