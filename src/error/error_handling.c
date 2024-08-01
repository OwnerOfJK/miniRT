/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 21:50:43 by jkaller           #+#    #+#             */
/*   Updated: 2024/08/01 20:45:32 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

//this function should also free whatever needs to be freed

void	error_free_data(t_data *data, char *error_message)
{
	if (data != NULL)
		free_data(data);
	ft_putstr_fd(error_message, 2);
	exit(EXIT_FAILURE);
}

int	clean_exit(t_data *data)
{
	free_data(data);
	exit(EXIT_SUCCESS);
}

int	error_free_nothing(char *error_message)
{
	ft_putstr_fd(error_message, 2);
	exit(EXIT_SUCCESS);
}
