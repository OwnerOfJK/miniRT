/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:08:26 by jkaller           #+#    #+#             */
/*   Updated: 2024/07/30 16:08:42 by jkaller          ###   ########.fr       */
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
	int	len;

	len = m_len(matrix);
	i = 0;
	while (i < len)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}