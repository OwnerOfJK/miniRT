/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 23:20:40 by jkaller           #+#    #+#             */
/*   Updated: 2024/06/03 16:11:44 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	free_double_pointer(char **double_pointer)
{
	int	i;

	i = 0;
	while (double_pointer[i] != NULL)
	{
		free(double_pointer[i]);
		i++;
	}
	free(double_pointer);
}

void	free_matrix(double **matrix)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}
