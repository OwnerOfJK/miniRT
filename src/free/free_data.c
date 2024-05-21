/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 23:20:40 by jkaller           #+#    #+#             */
/*   Updated: 2024/05/21 23:51:56 by jkaller          ###   ########.fr       */
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
