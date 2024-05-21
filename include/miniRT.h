/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:48:02 by jkaller           #+#    #+#             */
/*   Updated: 2024/05/22 00:47:49 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

/* External Libraries */
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

/* Internal Libraries */
# include "../libs/libft/libft.h"
# include "../libs/mlx_linux/mlx.h"

/* Data Structures */

/* Parsing */
void	parse_input(char *file_path);

/* Error Handling */
void	error_message(char *error_message);
char	**check_config(char *file_path);
void	check_information(char **object_configs);

/* Utils */
void	print_double_pointer(char **double_pointer);
int		get_config_len(char *file_path);

/* Free Memory */
void	free_double_pointer(char **double_pointer);

#endif