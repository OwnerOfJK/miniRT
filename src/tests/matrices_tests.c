/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices_tests.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:30:42 by jkaller           #+#    #+#             */
/*   Updated: 2024/06/04 16:20:17 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void print_matrix(double **matrix)
{
	int row;
	int column;

	row = 0;
	while (row < m_len(matrix))
	{
		column = 0;
		while (column < m_len(matrix))
		{
			printf("%8.2f ", matrix[row][column]);
			column++;
		}
		printf("\n");
		row++;
	}
}

// Function to initialize a 4x4 matrix with specific values

double**	initialize_matrix(double **values, int len)
{
	double **matrix = (double **)malloc((len + 1) * sizeof(double *));
	for (int i = 0; i < (len); ++i)
	{
		matrix[i] = (double *)malloc((len) * sizeof(double));
		for (int j = 0; j < (len); ++j) {
			matrix[i][j] = values[i][j];
		}
	}
	matrix[len] = NULL;
	return (matrix);
}

void test_m_len(void)
{
	double u_vals[4][4] = {
		{ 1, 2, 3, 4 },
		{ 5, 6, 7, 8 },
		{ 9, 10, 11, 12 },
		{ 13, 14, 15, 16 }
	};
	double *u_ptr[4] = { u_vals[0], u_vals[1], u_vals[2], u_vals[3] };
	double** u = initialize_matrix(u_ptr, 4);
	assert(m_len(u) == 4);
	free_matrix(u);
}

// Test for m_mult
void test_m_mult()
{
	double u_vals[4][4] = {
		{ 1, 2, 3, 4 },
		{ 5, 6, 7, 8 },
		{ 9, 10, 11, 12 },
		{ 13, 14, 15, 16 }
	};
	double *u_ptr[4] = { u_vals[0], u_vals[1], u_vals[2], u_vals[3] };
	double v_vals[4][4] = {
		{ 17, 18, 19, 20 },
		{ 21, 22, 23, 24 },
		{ 25, 26, 27, 28 },
		{ 29, 30, 31, 32 }
	};
	double *v_ptr[4] = { v_vals[0], v_vals[1], v_vals[2], v_vals[3] };
	double expected_vals[4][4] = {
		{ 250, 260, 270, 280 },
		{ 618, 644, 670, 696 },
		{ 986, 1028, 1070, 1112 },
		{ 1354, 1412, 1470, 1528 }
	};
	double *expected_vals_ptr[4] = { expected_vals[0], expected_vals[1], expected_vals[2], expected_vals[3] };

	double **u = initialize_matrix(u_ptr, 4);
	double **v = initialize_matrix(v_ptr, 4);
	double **expected_result = initialize_matrix(expected_vals_ptr, 4);

	double **result = m_mult(u, v);
	assert(m_compare(result, expected_result) == 1);

	free_matrix(u);
	free_matrix(v);
	free_matrix(expected_result);
	free_matrix(result);
}

// Test for mv_mult
void test_mv_mult()
{
	double u_vals[4][4] = {
		{ 1, 2, 3, 4 },
		{ 5, 6, 7, 8 },
		{ 9, 10, 11, 12 },
		{ 13, 14, 15, 16 }
	};
	double *u_ptr[4] = { u_vals[0], u_vals[1], u_vals[2], u_vals[3] };

	t_vector v = { 1, 2, 3, 4 };
	t_vector expected_result = { 30, 70, 110, 150 };
	double **u = initialize_matrix(u_ptr, 4);
	t_vector result = mv_mult(u, v);
	assert(result.x == expected_result.x);
	assert(result.y == expected_result.y);
	assert(result.z == expected_result.z);
	assert(result.w == expected_result.w);
	free_matrix(u);
}

// Test for m_identity
void test_m_identity()
{
	double u_vals[4][4] = {
		{ 1, 2, 3, 4 },
		{ 5, 6, 7, 8 },
		{ 9, 10, 11, 12 },
		{ 13, 14, 15, 16 }
	};
	double *u_ptr[4] = { u_vals[0], u_vals[1], u_vals[2], u_vals[3] };

	double** u = initialize_matrix(u_ptr, 4);
	double** result = m_identity(u);

	assert(m_compare(result, u) == 1);

	free_matrix(u);
	free_matrix(result);
}

// Test for m_transpose
void test_m_transpose()
{
	double u_vals[4][4] = {
		{ 1, 2, 3, 4 },
		{ 5, 6, 7, 8 },
		{ 9, 10, 11, 12 },
		{ 13, 14, 15, 16 }
	};
	double *u_ptr[4] = { u_vals[0], u_vals[1], u_vals[2], u_vals[3] };
	double** u = initialize_matrix(u_ptr, 4);

	double expected_vals[4][4] = {
		{ 1, 5, 9, 13 },
		{ 2, 6, 10, 14 },
		{ 3, 7, 11, 15 },
		{ 4, 8, 12, 16 }
	};
	double *expected_vals_ptr[4] = { expected_vals[0], expected_vals[1], expected_vals[2], expected_vals[3] };
	double** expected_result = initialize_matrix(expected_vals_ptr, 4);

	double **result = m_transpose(u);
	assert(m_compare(result, expected_result) == 1);

	free_matrix(u);
	free_matrix(expected_result);
	free_matrix(result);
}

// Test for m_determinant
void tets_m_determinant()
{
	double u_vals[3][3] = {
		{ 3, 5, 0},
		{ 2, -1, -7},
		{ 6, -1, 5}
	};
	double *u_vals_ptr[3] = { u_vals[0], u_vals[1], u_vals[2]};
	double** u = initialize_matrix(u_vals_ptr, 3);
	double u_test[2][2] = {
		{ 2, -7},
		{ 6, 5}
	};
	double *u_test_ptr[3] = { u_test[0], u_test[1]};
	double** test = initialize_matrix(u_test_ptr, 2);
	double determinant = m_determinant(test);
	double minor = m_minor(u, 0, 1);
	assert(determinant == minor);
	free_matrix(u);
	free_matrix(test);
}

void tets_m_cofactor()
{
	double u_vals[3][3] =
	{
		{ 1, 2, 6},
		{ -5, 8, -4},
		{ 2, 6, 4}
	};
	double *u_vals_ptr[3] = { u_vals[0], u_vals[1], u_vals[2]};
	double** u = initialize_matrix(u_vals_ptr, 3);
	double cofactor = m_cofactor(u, 0, 0);
	assert(cofactor == 56);
	cofactor = m_cofactor(u, 0, 1);
	assert(cofactor == 12);
	cofactor = m_cofactor(u, 0, 2);
	assert(cofactor == -46);
	free_matrix(u);
}

void tets_m4_cofactor()
{
	double u_vals[4][4] =
	{
		{ -2, -8, 3, 5},
		{ -3, 1, 7, 3},
		{ 1, 2, -9, 6},
		{ -6, 7, 7, -9}
	};
	double *u_vals_ptr[4] = { u_vals[0], u_vals[1], u_vals[2], u_vals[3]};
	double** u = initialize_matrix(u_vals_ptr, 4);
	double cofactor = m_cofactor(u, 0, 0);
	assert(cofactor == 690);
	cofactor = m_cofactor(u, 0, 1);
	assert(cofactor == 447);
	cofactor = m_cofactor(u, 0, 2);
	assert(cofactor == 210);
	cofactor = m_cofactor(u, 0, 3);
	assert(cofactor == 51);
	double determinant = m_determinant(u);
	assert(determinant == -4071);
	free_matrix(u);
}

void test_m_determinant_check()
{
	double u_vals[4][4] =
	{
		{ 6, 4, 4, 4},
		{ 5, 5, 7, 6},
		{ 4, -9, 3, -7},
		{ 9, 1, 7, -6}
	};
	double *u_vals_ptr[4] = { u_vals[0], u_vals[1], u_vals[2], u_vals[3]};
	double** u = initialize_matrix(u_vals_ptr, 4);
	double determinant = m_determinant(u);
	assert(determinant == -2120);
	double u_vals2[4][4] =
	{
		{ -4, 2, -2, -3},
		{ 9, 6, 2, 6},
		{ 0, -5, 1, -5},
		{ 0, 0, 0, 0}
	};
	double *u_vals_ptr2[4] = { u_vals2[0], u_vals2[1], u_vals2[2], u_vals2[3]};
	double** u2 = initialize_matrix(u_vals_ptr2, 4);
	double determinant2 = m_determinant(u2);
	assert(determinant2 == 0);
	free_matrix(u2);
	free_matrix(u);
}

void test_m_inverse()
{
	double u_vals[4][4] =
	{
		{ -5, 2, 6, -8},
		{ 1, -5, 1, 8},
		{ 7, 7, -6, -7},
		{ 1, -3, 7, 4}
	};
	double *u_vals_ptr[4] = { u_vals[0], u_vals[1], u_vals[2], u_vals[3]};
	double** u = initialize_matrix(u_vals_ptr, 4);
	double** inverse = m_inverse(u);
	double expected_vals[4][4] =
	{
		{ 0.21805, 0.45113, 0.24060, -0.04511},
		{ -0.80827, -1.45677, -0.44361, 0.52068},
		{ -0.07895, -0.22368, -0.05263, 0.19737},
		{ -0.52256, -0.81391, -0.30075, 0.30639}
	};
	double *expected_vals_ptr[4] = { expected_vals[0], expected_vals[1], expected_vals[2], expected_vals[3]};
	double** expected_result = initialize_matrix(expected_vals_ptr, 4);
	assert(m_compare(inverse, expected_result) == 1);
	free_matrix(u);
	free_matrix(inverse);
	free_matrix(expected_result);


	double u_vals2[4][4] =
	{
		{ 8, -5, 9, 2},
		{ 7, 5, 6, 1},
		{ -6, 0, 9, 6},
		{ -3, 0, -9, -4}
	};
	double *u_vals_ptr2[4] = { u_vals2[0], u_vals2[1], u_vals2[2], u_vals2[3]};
	double** u2 = initialize_matrix(u_vals_ptr2, 4);
	double** inverse2 = m_inverse(u2);
	double expected_vals2[4][4] =
	{
		{ -0.15385, -0.15385, -0.28205, -0.53846},
		{ -0.07692, 0.12308, 0.02564, 0.03077},
		{ 0.35897, 0.35897, 0.43590, 0.92308},
		{ -0.69231, -0.69231, -0.76923, -1.92308}
	};
	double *expected_vals_ptr2[4] = { expected_vals2[0], expected_vals2[1], expected_vals2[2], expected_vals2[3]};
	double** expected_result2 = initialize_matrix(expected_vals_ptr2, 4);
	assert(m_compare(inverse2, expected_result2) == 1);
	free_matrix(u2);
	free_matrix(inverse2);
	free_matrix(expected_result2);
	
	double u_vals3[4][4] =
	{
		{ 9, 3, 0, 9},
		{ -5, -2, -6, -3},
		{ -4, 9, 6, 4},
		{ -7, 6, 6, 2}
	};
	double *u_vals_ptr3[4] = { u_vals3[0], u_vals3[1], u_vals3[2], u_vals3[3]};
	double** u3 = initialize_matrix(u_vals_ptr3, 4);
	double** inverse3 = m_inverse(u3);
	double expected_vals3[4][4] =
	{
		{ -0.04074, -0.07778, 0.14444, -0.22222},
		{ -0.07778, 0.03333, 0.36667, -0.33333},
		{ -0.02901, -0.14630, -0.10926, 0.12963},
		{ 0.17778, 0.06667, -0.26667, 0.33333}
	};
	double *expected_vals_ptr3[4] = { expected_vals3[0], expected_vals3[1], expected_vals3[2], expected_vals3[3]};
	double** expected_result3 = initialize_matrix(expected_vals_ptr3, 4);
	assert(m_compare(inverse3, expected_result3) == 1);
	free_matrix(u3);
	free_matrix(inverse3);
	free_matrix(expected_result3);
}

/* This is to mutiply two matrixes and see if the inverse can return it*/
void	test_m_inverse_mult()
{
	double u_vals[4][4] =
	{
		{ 3, -9, 7, 3},
		{ 3, -8, 2, -9},
		{ -4, 4, 4, 1},
		{ -6, 5, -1, 1}
	};
	double *u_vals_ptr[4] = { u_vals[0], u_vals[1], u_vals[2], u_vals[3]};
	double** u = initialize_matrix(u_vals_ptr, 4);
	double v_vals[4][4] =
	{
		{ 8, 2, 2, 2},
		{ 3, -1, 7, 0},
		{ 7, 0, 5, 4},
		{ 6, -2, 0, 5}
	};
	double *v_vals_ptr[4] = { v_vals[0], v_vals[1], v_vals[2], v_vals[3]};
	double** v = initialize_matrix(v_vals_ptr, 4);
	double** result = m_mult(u, v);
	double** inverse = m_inverse(v);
	double** expected_result = m_mult(result, inverse);
	assert(m_compare(expected_result, u) == 1);
	free_matrix(u);
	free_matrix(v);
	free_matrix(result);
	free_matrix(inverse);
	free_matrix(expected_result);
}

// Main function to execute all tests
int test_matrices()
{
	test_m_len();
	test_m_mult();
	test_mv_mult();
	test_m_identity();
	test_m_transpose();
	tets_m_determinant();
	tets_m_cofactor();
	tets_m4_cofactor();
	test_m_determinant_check();
	test_m_inverse();
	test_m_inverse_mult();

	printf("All matrices tests passed!\n");

	return (0);
}
