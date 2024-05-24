/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:48:02 by jkaller           #+#    #+#             */
/*   Updated: 2024/05/24 20:52:26 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

/* External Libraries */
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# ifndef PI
#  define PI 3.14159265358979323846
# endif

/* Internal Libraries */
# include "../libs/libft/libft.h"
# include "../libs/mlx_linux/mlx.h"

/* Data Structures */

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}	t_vector;


/* Parsing */
void		parse_input(char *file_path);

/* Error Handling */
void		error_message(char *error_message);
char		**check_config(char *file_path);
void		check_information(char **object_configs);

/*math utils*/
t_vector	v_add(t_vector u, t_vector v);
t_vector	v_sub(t_vector u, t_vector v);
t_vector	v_mult(t_vector u, t_vector v);
double		v_dot(t_vector u, t_vector v);
t_vector	v_scalar(t_vector u, double t);
int			v_compare(t_vector u, t_vector v);
t_vector	v_init(double x, double y, double z);
t_vector	v_cross(t_vector u, t_vector v);
t_vector	v_neg(t_vector u);


/* Utils */
void		print_double_pointer(char **double_pointer);
int			get_config_len(char *file_path);

/* Free Memory */
void		free_double_pointer(char **double_pointer);



/*debug utils*/
//need to delete later
void		vec_print(t_vector vec);

#endif
