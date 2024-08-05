/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:19:46 by jkaller           #+#    #+#             */
/*   Updated: 2024/08/05 19:20:21 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

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

void	copy_submatrix(t_submatrix sub, double **u, int row, int column)
{
	while (sub.i < sub.len)
	{
		if (sub.i != row)
		{
			sub.j = 0;
			sub.y = 0;
			while (sub.j < sub.len)
			{
				if (sub.j != column)
				{
					sub.submatrix[sub.x][sub.y] = u[sub.i][sub.j];
					sub.y++;
				}
				sub.j++;
			}
			sub.x++;
		}
		sub.i++;
	}
}

double	**m_submatrix(double **u, int row, int column)
{
	t_submatrix	sub;

	sub.x = 0;
	sub.y = 0;
	sub.len = m_len(u);
	sub.submatrix = m_init(sub.len - 1);
	sub.i = 0;
	copy_submatrix(sub, u, row, column);
	return (sub.submatrix);
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
