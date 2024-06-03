/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:19:46 by jkaller           #+#    #+#             */
/*   Updated: 2024/06/03 20:36:23 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

double	**m_transpose(double **u)
{
	double	**transpose;
	int		row;
	int		column;

	transpose = m_init(4);
	row = 0;
	while (row < 4)
	{
		column = 0;
		while (column < 4)
		{
			transpose[row][column] = u[column][row];
			column++;
		}
		row++;
	}
	return (transpose);
}

double	m_determinant(double **u)
{
	double	det;

	det = (u[0][0] * u[1][1]) - (u[0][1] * u[1][0]);
	return (det);
}
double	**m_submatrix(double **u, int row, int column, int m_len)
{
	double	**submatrix;
	int		i;
	int		j;
	int		x;
	int		y;

	submatrix = m_init(m_len - 1);
	i = 0;
	x = 0;
	while (i < m_len)
	{
		if (i != row)
		{
			j = 0;
			y = 0;
			while (j < m_len)
			{
				if (j != column && i != row)
				{
					submatrix[y][x] = u[j][i];
					y++;
				}
				j++;
			}
			x++;
		}
		i++;
	}
	return (submatrix);
}

double	m_minor(double **u, int row, int column, int m_len)
{
	double	**submatrix;
	double	det;

	submatrix = m_submatrix(u, row, column, m_len);
	det = m_determinant(submatrix);
	free_matrix(submatrix, m_len - 1);
	return (det);
}

double	m_cofactor(double **u, int row, int column, int m_len)
{
	double	minor;

	minor = m_minor(u, row, column, m_len);
	if ((row + column) % 2 == 0)
		return (minor);
	else
		return (-minor);
}

