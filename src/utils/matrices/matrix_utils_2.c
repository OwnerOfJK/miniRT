/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:26:51 by jkaller           #+#    #+#             */
/*   Updated: 2024/08/05 19:19:56 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

int	m_len(double **matrix)
{
	int	i;

	i = 0;
	if (!matrix)
		return (0);
	while (matrix[i])
		i++;
	return (i);
}

double	**m_inverse(double **matrix)
{
	double	**inverse;
	double	det;
	int		row;
	int		column;
	int		len;

	row = 0;
	column = 0;
	len = m_len(matrix);
	inverse = m_init(len);
	det = m_determinant(matrix);
	if (det == 0)
		return (NULL);
	while (row < len)
	{
		column = 0;
		while (column < len)
		{
			inverse[column][row] = m_cofactor(matrix, row, column) / det;
			column++;
		}
		row++;
	}
	return (inverse);
}

double	**m_translate(t_vector translation)
{
	double	**translation_matrix;

	translation_matrix = m_init(4);
	translation_matrix[0][0] = 1;
	translation_matrix[1][1] = 1;
	translation_matrix[2][2] = 1;
	translation_matrix[3][3] = 1;
	translation_matrix[0][3] = translation.x;
	translation_matrix[1][3] = translation.y;
	translation_matrix[2][3] = translation.z;
	return (translation_matrix);
}

double	**m_scale(t_vector scale)
{
	double	**scale_matrix;

	scale_matrix = m_init(4);
	scale_matrix[0][0] = scale.x;
	scale_matrix[1][1] = scale.y;
	scale_matrix[2][2] = scale.z;
	scale_matrix[3][3] = 1;
	return (scale_matrix);
}

t_vector	m_reflect(t_vector normal)
{
	t_vector	reflect_vector;

	reflect_vector = v_init(-1, 1, 1, 1);
	return (mv_mult(m_scale(reflect_vector), normal));
}
