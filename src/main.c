/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:39:45 by jkaller           #+#    #+#             */
/*   Updated: 2024/06/15 14:30:16 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

int	main(int argc, char **argv)
{
	t_data	*data;
	t_input	*input;

	//test_vectors();
	test_matrices();

	if (argc != 2)
		error_message("Error: Wrong number of arguments\n");
	input = parse_input(argv[1]);
	test_intersections(input);
	// if (check_input(argv[1]) == EXIT_SUCCESS)
	// 	parse_input(argv[1]);
	data = malloc(sizeof(t_data));
	//ft_memset(data, 0, sizeof(t_data)); //delete later
	data = create_world(data);
	launching_mlx(data); //need to add the data
	render_scene(data);
	clean_exit(data);
	return (0);
}
