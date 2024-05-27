/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:39:45 by jkaller           #+#    #+#             */
/*   Updated: 2024/05/27 18:34:31 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

int	main(int argc, char **argv)
{
	t_data *data;

	if (argc != 2)
		error_message("Error: Wrong number of arguments\n");
	//(void)argv;
	parse_input(argv[1]);
	// if (check_input(argv[1]) == EXIT_SUCCESS)
	// 	parse_input(argv[1]);
	data = malloc(sizeof(t_data));
	ft_memset(data, 0, sizeof(t_data)); //delete later
	launching_mlx(data); //need to add the data
	//destroy_mlx(&data);
	return (0);
}
