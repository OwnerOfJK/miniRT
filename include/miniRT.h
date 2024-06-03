/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:48:02 by jkaller           #+#    #+#             */
/*   Updated: 2024/06/03 13:46:56 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

/* External Libraries */
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <X11/keysym.h>

/* Internal Libraries */
# include "../libs/libft/libft.h"
# include "../libs/mlx_linux/mlx.h"

# ifndef PI
#  define PI 3.14159265358979323846
# endif

# ifndef WIDTH
#  define WIDTH 800
# endif

# ifndef EPSILON
#  define EPSILON 0.0001
# endif

# ifndef HEIGHT
#  define HEIGHT 800
# endif

# define EPSILON 0.0001



/* Data Structures */
typedef struct s_color
{
	double	r;
	double	g;
	double	b;
}	t_color;

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
	double	w;
}	t_vector;




/*
origin : starting point
direction : where it points
*/
typedef struct s_ray
{
	t_vector	origin;
	t_vector	direction;
}	t_ray;

/*
	Usefull for second degree equations
	a The a value
	b The b value
	c The c value
	t1 The first root
	t2 The second root
*/
typedef struct s_equat2
{
	double	a;
	double	b;
	double	c;
	double	t1;
	double	t2;
}	t_equat2;

/*
∗ ambient lighting ratio in range [0.0,1.0]: 0.2
∗ R,G,B colors in range [0-255]: 255, 255, 255
*/
typedef struct s_alightning
{
	double		ratio;
	t_color		*color;
}	t_alightning;

/*
∗ x,y,z coordinates of the view point: -50.0,0,20
∗ 3d normalized orientation vector. In range [-1,1] for each x,y,z axis:
0.0,0.0,1.0
∗ FOV : Horizontal field of view in degrees in range [0,180]: 70
*/
typedef struct s_camera
{
	t_vector	*pos;
	t_vector	*orientation_vector;
	double		fov;
}	t_camera;

/*
∗ x,y,z coordinates of the light point: -40.0,50.0,0.0
∗ the light brightness ratio in range [0.0,1.0]: 0.6
∗ (unused in mandatory part)R,G,B colors in range [0-255]: 10, 0, 255
*/
typedef struct s_light
{
	t_vector	*pos;
	double		brightness;
}	t_light;

/* Used to generalise linked lists */
typedef struct s_base_node
{
	struct s_base_node	*next;
}	t_base_node;

/*
∗ x,y,z coordinates of the sphere center: 0.0,0.0,20.6
∗ the sphere diameter: 12.6
∗ R,G,B colors in range [0-255]: 10, 0, 255
*/
typedef struct s_sphere
{
	t_base_node		base;
	t_vector		*pos;
	double			diameter;
	t_color			*color;
	struct s_sphere	*next;
}	t_sphere;

/*
∗ x,y,z coordinates of a point in the plane: 0.0,0.0,-10.0
∗ 3d normalized normal vector. In range [-1,1] for each x,y,z axis: 0.0,1.0,0.0
∗ R,G,B colors in range [0-255]: 0,0,225
*/
typedef struct s_plane
{
	t_base_node		base;
	t_vector		*pos;
	t_vector		*normal_vector;
	t_color			*color;
	struct s_plane	*next;
}	t_plane;

/*
∗ x,y,z coordinates of the center of the cylinder: 50.0,0.0,20.6
∗ 3d normalized vector of axis of cylinder. In range [-1,1] for each x,y,z axis:
0.0,0.0,1.0
∗ the cylinder diameter: 14.2
∗ the cylinder height: 21.42
∗ R,G,B colors in range [0,255]: 10, 0, 255
*/
typedef struct s_cylinder
{
	t_base_node			base;
	t_vector			*pos;
	t_vector			*axis_vector;
	double				diameter;
	double				height;
	t_color				*color;
	struct s_cylinder	*next;
}	t_cylinder;

typedef struct s_input
{
	t_alightning		*alightning;
	t_camera			*camera;
	t_light				*light;
	t_sphere			*sphere;
	t_plane				*plane;
	t_cylinder			*cylinder;
}	t_input;


typedef struct s_graphics
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;

}	t_graphics;

typedef struct s_data
{
	t_graphics	display;
}	t_data;

/*
	shape the shape that was hit
	ray The ray that hit the shape
	t The intersection point
	color The color of the hit shape
*/
/*
typedef struct s_hit
{
	t_ray		ray;
	t_vector	t;
	t_color		color;
}	t_hit;
*/

/* Parsing */
t_input			*parse_input(char *file_path);
t_alightning	*parse_alightning(char **object_configs);
t_camera		*parse_camera(char **object_configs);
t_light			*parse_light(char **object_configs);
t_sphere		*parse_sphere(char **object_configs);
t_plane			*parse_plane(char **object_configs);
t_cylinder		*parse_cylinder(char **object_configs);
t_color			*parse_color(char *str);
t_vector		*parse_coordinate(char *str);
t_vector		*parse_vector(char *str);

/* Linked List Parsing*/
t_sphere		*ft_lstnew_sphere(char *str);
t_plane			*ft_lstnew_plane(char *str);
t_cylinder		*ft_lstnew_cylinder(char *str);
void			ft_lstadd_back_miniRT(t_base_node **lst, t_base_node *new);

/*init*/
void			launching_mlx(t_data *data);
int				key_handler(int keysym, t_data *data);
void			event_init(t_data *data);

/* Error Handling */
void			error_message(char *error_message);
void			error_free(t_data *data, char *error_message);
char			**check_config(char *file_path);
void			check_information(char **object_configs);
//void			malloc_error(void);
int				clean_exit(t_data *data);

/*math utils*/
t_vector		v_add(t_vector u, t_vector v);
t_vector		v_sub(t_vector u, t_vector v);
t_vector		v_mult(t_vector u, t_vector v);
double			v_dot(t_vector u, t_vector v);
t_vector		v_scalar(t_vector u, double t);
int				v_compare(t_vector u, t_vector v);
t_vector		v_init(double x, double y, double z, double w);
t_vector		v_cross(t_vector u, t_vector v);
t_vector		v_neg(t_vector u);
double			v_length(t_vector v);
t_vector		v_normalize(t_vector v);
double			calc_delta(double a, double b, double c);
double			solve_quadratic(t_equat2 *eq);

/* Utils */
void			print_double_pointer(char **double_pointer);
int				get_config_len(char *file_path);
char			**find_index(char** object_configs, char *index, int len);
char			*find_and_extract_double(char *str, int pos);

/* Free Memory */
void			free_double_pointer(char **double_pointer);

/* Rendering */
void			render_scene(t_data *data);
void			my_mlx_pixel_put(t_graphics *img, int x, int y, int color);

/*debug utils*/
//need to delete later
void			vec_print(t_vector vec);
void			print_input(t_input *input);


#endif
