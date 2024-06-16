/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:39:45 by jkaller           #+#    #+#             */
/*   Updated: 2024/06/16 15:53:19 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

int	main(int argc, char **argv)
{
	t_data	*data;
	//t_data	*input;

	//test_vectors();
	//test_matrices();

	if (argc != 2)
		error_message("Error: Wrong number of arguments\n");
	data = malloc(sizeof(t_data));
	data->data = parse_input(argv[1]);
	//test_intersections(data->data);
	// if (check_input(argv[1]) == EXIT_SUCCESS)
	// 	parse_input(argv[1]);
	////ft_memset(data, 0, sizeof(t_data)); //delete later
	//data = create_world(data, input);
	test_proof_of_concept(data);
	//launching_mlx(data); //need to add the data
	render_scene(data);
	//clean_exit(data);
	return (0);
}
