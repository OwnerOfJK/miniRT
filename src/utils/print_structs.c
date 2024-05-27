/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_structs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 23:13:40 by jkaller           #+#    #+#             */
/*   Updated: 2024/05/27 23:58:03 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	print_double_pointer(char **double_pointer)
{
	int	i;

	i = 0;
	while (double_pointer[i] != NULL)
	{
		ft_printf("%s\n", double_pointer[i]);
		i++;
	}
}

void	print_camera(t_camera *camera)
{
	printf("Camera\n");
	printf("Position: %f %f %f\n", camera->pos->x, camera->pos->y, camera->pos->z);
	printf("Direction: %f %f %f\n", camera->orientation_vector->x, camera->orientation_vector->y, camera->orientation_vector->z);
	printf("FOV: %f\n", camera->fov);
}

void	print_alightning(t_alightning *alightning)
{
	printf("Ambient lightning:\n");
	printf("Ratio: %f\n", alightning->ratio);
	printf("Color: %f %f %f\n", alightning->color->r, alightning->color->g, alightning->color->b);
}

void	print_input(t_input *input)
{
	print_alightning(input->alightning);
	print_camera(input->camera);
}
