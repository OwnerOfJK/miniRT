/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:24:34 by jkaller           #+#    #+#             */
/*   Updated: 2024/07/31 18:35:23 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

void	compute_rotation_components(double angle,
		double *c, double *s, double *t)
{
	*c = cos(angle);
	*s = sin(angle);
	*t = 1 - *c;
}

double	**m_rotation(t_vector axis, double angle)
{
	double	**matrix;
	double	c;
	double	s;
	double	t;

	matrix = m_init(4);
	compute_rotation_components(angle, &c, &s, &t);
	matrix[0][0] = t * axis.x * axis.x + c;
	matrix[0][1] = t * axis.x * axis.y - s * axis.z;
	matrix[0][2] = t * axis.x * axis.z + s * axis.y;
	matrix[0][3] = 0;
	matrix[1][0] = t * axis.x * axis.y + s * axis.z;
	matrix[1][1] = t * axis.y * axis.y + c;
	matrix[1][2] = t * axis.y * axis.z - s * axis.x;
	matrix[1][3] = 0;
	matrix[2][0] = t * axis.x * axis.z - s * axis.y;
	matrix[2][1] = t * axis.y * axis.z + s * axis.x;
	matrix[2][2] = t * axis.z * axis.z + c;
	matrix[2][3] = 0;
	matrix[3][0] = 0;
	matrix[3][1] = 0;
	matrix[3][2] = 0;
	matrix[3][3] = 1;
	return (matrix);
}
