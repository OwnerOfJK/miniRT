/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:19:46 by jkaller           #+#    #+#             */
/*   Updated: 2024/07/31 21:00:17 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

double	**m_transpose(double **u)
{
	double	**transpose;
	int		row;
	int		column;
	int		len;

	transpose = m_init(4);
	row = 0;
	len = m_len(u);
	while (row < len)
	{
		column = 0;
		while (column < len)
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
	int		len;
	int		column;

	len = m_len(u);
	det = 0;
	column = 0;
	if (len == 2)
		det = (u[0][0] * u[1][1]) - (u[0][1] * u[1][0]);
	else if (len > 2)
	{
		while (column < len)
		{
			det += u[0][column] * m_cofactor(u, 0, column);
			column++;
		}
	}
	return (det);
}

double	**m_submatrix(double **u, int row, int column)
{
	double	**submatrix;
	int		i;
	int		j;
	int		x;
	int		y;
	int		len;

	x = 0;
	y = 0;
	len = m_len(u);
	submatrix = m_init(len - 1);
	i = 0;
	while (i < len)
	{
		if (i != row)
		{
			j = 0;
			y = 0;
			while (j < len)
			{
				if (j != column)
				{
					submatrix[x][y] = u[i][j];
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

double	m_minor(double **u, int row, int column)
{
	double	**submatrix;
	double	det;

	submatrix = m_submatrix(u, row, column);
	det = m_determinant(submatrix);
	free_matrix(submatrix);
	return (det);
}

double	m_cofactor(double **u, int row, int column)
{
	double	minor;

	minor = m_minor(u, row, column);
	if ((row + column) % 2 == 0)
		return (minor);
	else
		return (-minor);
}
