/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils_0.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 13:20:48 by jkaller           #+#    #+#             */
/*   Updated: 2024/06/03 19:55:45 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

double	**m_init(int m_len)
{
	double	**matrix;
	int		i;

	matrix = malloc(sizeof(double *) * m_len);
	i = 0;
	while (i < m_len)
	{
		matrix[i] = ft_calloc(m_len, sizeof(double));
		i++;
	}
	return (matrix);
}

/* This doesn't free the matrix, reminder for us to free it.*/
double	**m_mult(double **u, double **v)
{
	int		row;
	int		column;
	int		k;
	double	**result;

	k = 0;
	row = 0;
	result = m_init(4);
	while (row < 4)
	{
		column = 0;
		while (column < 4)
		{
			result[row][column] = 0;
			k = 0;
			while (k < 4)
			{
				result[row][column] += u[row][k] * v[k][column];
				k++;
			}
			column++;
		}
		row++;
	}
	return (result);
}

t_vector	mv_mult(double **u, t_vector v)
{
	t_vector	w;
	int			row;

	w = v_init(0.0, 0.0, 0.0, 0.0);
	row = 0;
	while (row < 4)
	{
		if (row == 0)
			w.x = u[row][0] * v.x + u[row][1]
				* v.y + u[row][2] * v.z + u[row][3] * v.w;
		if (row == 1)
			w.y = u[row][0] * v.x + u[row][1]
				* v.y + u[row][2] * v.z + u[row][3] * v.w;
		if (row == 2)
			w.z = u[row][0] * v.x + u[row][1]
				* v.y + u[row][2] * v.z + u[row][3] * v.w;
		if (row == 3)
			w.w = u[row][0] * v.x + u[row][1]
				* v.y + u[row][2] * v.z + u[row][3] * v.w;
		row++;
	}
	return (w);
}

/*
	Checks if two vectors are equal
*/
int	m_compare(double **u, double **v)
{
	int	row;
	int	column;

	row = 0;
	while (row < 4)
	{
		column = 0;
		while (column < 4)
		{
			if (u[row][column] != v[row][column])
				return (0);
			column++;
		}
		row++;
	}
	return (1);
}

double	**m_identity(double **u)
{
	int		row;
	int		column;
	double	**identity;
	double	**result;

	row = 0;
	identity = m_init(4);
	while (row < 4)
	{
		column = 0;
		while (column < 4)
		{
			if (row == column)
				identity[row][column] = 1;
			else
				identity[row][column] = 0;
			column++;
		}
		row++;
	}
	result = m_mult(u, identity);
	free_matrix(identity, 4);
	return (result);
}