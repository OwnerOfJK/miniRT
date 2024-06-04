/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:26:51 by jkaller           #+#    #+#             */
/*   Updated: 2024/06/04 15:57:24 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

int	m_len(double **matrix)
{
	int	i;

	i = 0;
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
