/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 13:20:48 by jkaller           #+#    #+#             */
/*   Updated: 2024/06/03 16:16:12 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

double	**m_init(void)
{
	double	**matrix;
	int		i;

	matrix = malloc(sizeof(double *) * 4);
	i = 0;
	while (i < 4)
	{
		matrix[i] = ft_calloc(4, sizeof(double));
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
	result = m_init();
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
	int			column;

	row = 0;
	while (row < 4)
	{
		column = 0;
		while (column < 4)
		{
			if (column == 0)
				w.x += u[row][column] * v.x;
			else if (column == 1)
				w.y += u[row][column] * v.x;
			else if (column == 2)
				w.z += u[row][column] * v.x;
			else if (column == 3)
				w.w += u[row][column] * v.x;
			column++;
		}
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
	identity = m_init();
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
	free_matrix(identity);
	return (result);
}

double	**m_transpose(double **u)
{
	double	**transpose;
	int		row;
	int		column;

	transpose = m_init();
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





