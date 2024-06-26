/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:39:45 by jkaller           #+#    #+#             */
/*   Updated: 2024/06/21 15:24:49 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

int	main(int argc, char **argv)
{
	t_data	*data;

	// test_vectors();
	// test_matrices();

	if (argc != 2)
		error_message("Error: Wrong number of arguments\n");
	data = data_init(argv);
	//test_intersections(data->input);
	//test_plane_intersect();
	// if (check_input(argv[1]) == EXIT_SUCCESS)
	// 	parse_input(argv[1]);
	//ft_memset(data, 0, sizeof(t_data)); //delete later
	launch_window(data);
	//launching_mlx(data); //need to add the data
	// render_scene(data);
	//clean_exit(data);
	return (0);
}
