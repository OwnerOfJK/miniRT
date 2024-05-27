/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 21:50:43 by jkaller           #+#    #+#             */
/*   Updated: 2024/05/27 16:57:46 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

//this function should also free whatever needs to be freed

void	error_message(char *error_message)
{

	//free stuff
	//destroy_mlx(t_data **data)
	ft_putstr_fd(error_message, 2);
	exit(EXIT_FAILURE);
}

void	error_free(t_data *data, char *error_message)
{
	(void)data;
	ft_putstr_fd(error_message, 2);
	exit(EXIT_FAILURE);
}

// void	destroy_mlx(t_data **data)
// {

// }
