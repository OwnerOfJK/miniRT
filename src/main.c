/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:39:45 by jkaller           #+#    #+#             */
/*   Updated: 2024/05/27 19:40:08 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

// static void test(void) {
//     t_vector u = v_init(1.0, 2.0, 3.0);
//     t_vector v = v_init(3.0, 4.0, 0.0);

//     printf("Initial vectors:\n");
//     vec_print(u);
//     vec_print(v);

//     printf("\nTesting v_add:\n");
//     t_vector add_result = v_add(u, v);
//     vec_print(add_result);

//     printf("\nTesting v_sub:\n");
//     t_vector sub_result = v_sub(u, v);
//     vec_print(sub_result);

//     printf("\nTesting v_mult:\n");
//     t_vector mult_result = v_mult(u, v);
//     vec_print(mult_result);

//     printf("\nTesting v_dot:\n");
//     double dot_result = v_dot(u, v);
//     printf("%f\n", dot_result);

//     printf("\nTesting v_scalar:\n");
//     t_vector scalar_result = v_scalar(u, 2.0);
//     vec_print(scalar_result);

//     printf("\nTesting v_compare:\n");
//     int compare_result = v_compare(u, v);
//     printf("%d\n", compare_result);

//     printf("\nTesting v_cross:\n");
//     t_vector cross_result = v_cross(u, v);
//     vec_print(cross_result);

//     printf("\nTesting v_neg:\n");
//     t_vector neg_result = v_neg(u);
//     vec_print(neg_result);

//     printf("\nTesting v_length:\n");
//     double length_result = v_length(v);
//     printf("%f\n", length_result);

//     printf("\nTesting v_normalize:\n");
//     t_vector normalize_result = v_normalize(v);
//     vec_print(normalize_result);
// }

int	main(int argc, char **argv)
{
	t_data *data;

	//test();
	if (argc != 2)
		error_message("Error: Wrong number of arguments\n");
	//(void)argv;
	parse_input(argv[1]);
	// if (check_input(argv[1]) == EXIT_SUCCESS)
	// 	parse_input(argv[1]);
	data = malloc(sizeof(t_data));
	ft_memset(data, 0, sizeof(t_data)); //delete later
	launching_mlx(data); //need to add the data
	clean_exit(data);
	return (0);
}
