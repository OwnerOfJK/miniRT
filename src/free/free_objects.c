/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:08:00 by jkaller           #+#    #+#             */
/*   Updated: 2024/07/30 16:26:36 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

// void	free_plane(t_vector *normal_vector)
// {
// 	free(normal_vector);
// }

// void	free_objects(t_object *objects)
// {
// 	t_object	*tmp;

// 	while (objects != NULL)
// 	{
// 		tmp = objects;
// 		objects = objects->next;
// 		if (tmp->type == PLANE)
// 			free_plane(tmp->shape.plane.normal_vector);
		
// 		free(tmp);
// 	}
// }