/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:08:00 by jkaller           #+#    #+#             */
/*   Updated: 2024/07/30 17:25:05 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	free_plane(t_object *plane)
{
	free(&(plane->pos));
	free(&(plane->color));
	free(&(plane->shape.plane.normal_vector));
	free(plane);
}

void	free_sphere(t_object *sphere)
{
	free(&(sphere->pos));
	free(&(sphere->color));
	free(sphere);
}

void	free_cylinder(t_object *cylinder)
{
	free(&(cylinder->pos));
	free(&(cylinder->color));
	free(&(cylinder->shape.cylinder.axis_vector));
	free(&(cylinder->shape.cylinder.cap_down));
	free(&(cylinder->shape.cylinder.cap_down));
	free(cylinder);
}

void	free_objects(t_object *objects)
{
	t_object	*tmp;

	while (objects != NULL)
	{
		tmp = objects;
		objects = objects->next;
		if (tmp->type == PLANE)
			free_plane(objects);
		else if (tmp->type == SPHERE)
			free_sphere(objects);
		else if (tmp->type == CYLINDER)
			free_cylinder(objects);
		free(tmp);
	}
}
