/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices_tests.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:30:42 by jkaller           #+#    #+#             */
/*   Updated: 2024/06/03 20:56:15 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void print_matrix(double **matrix, int m_len)
{
	int row;
	int column;

	row = 0;
	while (row < m_len)
	{
		column = 0;
		while (column < m_len)
		{
			printf("%8.2f ", matrix[row][column]);
			column++;
		}
		printf("\n");
		row++;
	}
}

// Function to initialize a 4x4 matrix with specific values

double** initialize_matrix(double **values, int m_len)
{
    double **matrix = (double **)malloc(m_len * sizeof(double *));
    for (int i = 0; i < m_len; ++i) {
        matrix[i] = (double *)malloc(m_len * sizeof(double));
        for (int j = 0; j < m_len; ++j) {
            matrix[i][j] = values[i][j];
        }
    }
    return matrix;
}

// Test for m_mult
void test_m_mult() {
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

	free_matrix(u, 4);
	free_matrix(v, 4);
	free_matrix(expected_result, 4);
	free_matrix(result, 4);
}

// Test for mv_mult
void test_mv_mult() {
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
	free_matrix(u, 4);
}

// Test for m_identity
void test_m_identity() {
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

	free_matrix(u, 4);
	free_matrix(result, 4);
}

// Test for m_transpose
void test_m_transpose() {
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

	free_matrix(u, 4);
	free_matrix(expected_result, 4);
	free_matrix(result, 4);
}

// Test for m_determinant
void tets_m_determinant() {
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
	double minor = m_minor(u, 1, 0, 3);
	assert(determinant == minor);
	free_matrix(u, 3);
	free_matrix(test, 2);
}

void tets_m_cofactor() {
	double u_vals[3][3] = {
		{ 1, 2, 6},
		{ -5, 8, -4},
		{ 2, 6, 4}
	};
	double *u_vals_ptr[3] = { u_vals[0], u_vals[1], u_vals[2]};
	double** u = initialize_matrix(u_vals_ptr, 3);
	double cofactor = m_cofactor(u, 0, 0, 3);
	printf("%f\n", cofactor);
	assert(cofactor == 56);
	cofactor = m_cofactor(u, 0, 1, 3);
	printf("%f\n", cofactor);
	assert(cofactor == 12);
	cofactor = m_cofactor(u, 0, 2, 3);
	printf("%f\n", cofactor);
	assert(cofactor == -46);
	free_matrix(u, 3);
}

// Main function to execute all tests
int test_matrices() {
	test_m_mult();
	test_mv_mult();
	test_m_identity();
	test_m_transpose();
	tets_m_determinant();
	tets_m_cofactor();

	printf("All matrices tests passed!\n");

	return (0);
}
