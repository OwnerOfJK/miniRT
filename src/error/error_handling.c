/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 21:50:43 by jkaller           #+#    #+#             */
/*   Updated: 2024/05/27 17:12:26 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

//this function should also free whatever needs to be freed

void	error_message(char *error_message)
{
	//free stuff
	ft_putstr_fd(error_message, 2);
	exit(EXIT_FAILURE);
}

void	error_free(t_data *data, char *error_message)
{
	(void)data;
	//destroy_mlx(t_data **data)
	if (error_message)
		ft_putstr_fd(error_message, 2);
	exit(EXIT_FAILURE);
}

// void	destroy_mlx(t_data **data)
// {

// }

int	clean_exit(t_data *data)
{
	mlx_destroy_image(data->display.mlx_ptr, data->display.img);
	mlx_destroy_window(data->display.mlx_ptr, data->display.win_ptr);
	mlx_destroy_display(data->display.mlx_ptr);
	free(data->display.mlx_ptr);
	exit(1);
}
