/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:48:02 by jkaller           #+#    #+#             */
/*   Updated: 2024/08/05 19:39:30 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

/* External Libraries */
#include <float.h>
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

# define BACKGROUND 0x000000

typedef int			t_color_mlx;

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

typedef struct s_coordinates {
	int	x;
	int	y;
} t_coordinates;

typedef struct s_submatrix {
	int 	i;
	int 	j;
	int 	x;
	int 	y;
	int 	len;
	double **submatrix;
} t_submatrix;

typedef struct s_material
{
	double		ambient;
	double		diffuse;
	double		specular;
	double		shininess;
}	t_material;

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
typedef struct s_alight
{
	double		ratio;
	t_color		color;
}	t_alight;

/*
∗ x,y,z coordinates of the view point: -50.0,0,20
∗ 3d normalized orientation vector. In range [-1,1] for each x,y,z axis:
0.0,0.0,1.0
∗ FOV : Horizontal field of view in degrees in range [0,180]: 70
*/
typedef struct s_camera
{
	t_vector	pos;
	t_vector	orientation_vector;
	double		fov;
}	t_camera;

/*
∗ x,y,z coordinates of the light point: -40.0,50.0,0.0
∗ the light brightness ratio in range [0.0,1.0]: 0.6
∗ (unused in mandatory part)R,G,B colors in range [0-255]: 10, 0, 255
*/
typedef struct s_light
{
	t_vector	pos;
	double		brightness;
}	t_light;

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

typedef struct s_viewport
{
	double	fov_radians;
	double	viewport_height;
	double	viewport_width;
}	t_viewport;

typedef enum {
    SPHERE,
    PLANE,
    CYLINDER
} t_obj_type;

/*
SPHERE
∗ x,y,z coordinates of the sphere center: 0.0,0.0,20.6
∗ the sphere diameter: 12.6
∗ R,G,B colors in range [0-255]: 10, 0, 255
*/

/*
PLANE
∗ x,y,z coordinates of a point in the plane: 0.0,0.0,-10.0
∗ 3d normalized normal vector. In range [-1,1] for each x,y,z axis: 0.0,1.0,0.0
∗ R,G,B colors in range [0-255]: 0,0,225
*/

/*
CYLINDER
∗ x,y,z coordinates of the center of the cylinder: 50.0,0.0,20.6
∗ 3d normalized vector of axis of cylinder. In range [-1,1] for each x,y,z axis:
0.0,0.0,1.0
∗ the cylinder diameter: 14.2
∗ the cylinder height: 21.42
∗ R,G,B colors in range [0,255]: 10, 0, 255
*/

typedef struct s_object {
    t_obj_type type;
    t_vector pos;
    t_color color;
    double **transformation_matrix;
	double **inverse_matrix;
    union {
        struct
		{
            double diameter;
        } sphere;
        struct
		{
            t_vector normal_vector;
        } plane;
        struct
		{
            t_vector axis_vector;
            double diameter;
            double height;
        } cylinder;
    } shape;
    struct s_object *next;
}	t_object;

typedef struct s_intersections
{
	int			hit;
	t_ray		ray;
	t_color		color;
	int			count;
	double		t1;
	double		t2;
	t_object	*object;
	t_vector	intersection_point;
	t_vector	normal;
}	t_intersections;

typedef struct s_input
{
	t_alight		*alight;
	t_camera		*camera;
	t_light			*light;
	t_object		*objects;
	t_material		*material;
	t_viewport		*viewport;
}	t_input;

typedef struct s_data //this is our world
{
	t_graphics		display;
	t_intersections	*intersections;
	t_input			*input;
	char			**object_configs;

}	t_data;

typedef struct s_context {
    t_data *data;
    t_object *objects_head;
    char *save_pointer;
    char *tmp;
} t_context;

/* Init */
t_material		*material_init(t_data *data);
t_ray			*ray_init(t_vector origin, t_vector direction);
t_viewport		*viewport_init(t_data *data, t_camera *camera);

/* Rendering */
void			launch_window(t_data *data);
void    		launch_mlx(t_data *data);
void			render(t_data *data);

/* Parsing */
t_input			*parse_input(t_data *data, char *file_path);
t_alight		*parse_alight(t_data *data, char **object_configs);
t_camera		*parse_camera(t_data *data, char **object_configs);
t_light			*parse_light(t_data *data, char **object_configs);
t_object		*parse_objects(t_data *data);
t_color			parse_color(char *str);
t_vector		parse_coordinate(char *str);
void			parse_light_attributes(t_light *light, char *save_pointer);
void			parse_cam_attributes(t_camera *camera, char *save_pointer);
void			parse_alight_attributes(t_alight *alight, char *save_pointer);
t_vector		parse_vector(char *str);
bool			check_nb_arg(char *save_pointer, int nb);
void			check_arg(t_data *data, t_input *input);

/* Linked List Parsing*/
t_object		*ft_lstnew_object(t_data *data, char *str, t_object	*objects_head);
t_object		*add_sphere(t_context *ctx, t_object *object, char *save_pointer);
t_object		*add_plane(t_context *ctx, t_object *object, char *save_pointer);
t_object		*add_cylinder(t_context *ctx, t_object *object, char *save_pointer);
void			ft_lstadd_back_minirt(t_object **lst, t_object *new);
void			compute_cylinder_m(t_object *object);
void			parse_cylinder_attributes(t_object *object, char *save_pointer);
void			parse_plane_attributes(t_object *object, char *save_pointer);
void			parse_sphere_attributes(t_object *object, char *save_pointer);

/*init*/
int				key_handler(int keysym, t_data *data);
void			event_init(t_data *data);
t_data			*data_init(char **argv);

/* Error Handling */
void			error_free_data(t_data *data, char *error_message);
void			check_config(t_data *data, char *file_path, int config_len);
void			check_information(t_data *data, char **object_configs);
int				clean_exit(t_data *data);
int				error_free_nothing(char *error_message);

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
t_vector		neg(t_vector u);

double			solve_quadratic_cy(t_equat2 *eq);
double			solve_quadratic(double a, double b, double c);
double			solve_quadratic_t2(double a, double b, double c);
double			set_intersections_t2(double t1, double t2);

/* Utils */
int				get_config_len(t_data *data, char *file_path);
char			**find_index(char** object_configs, char *index, int len);
char			*find_and_extract_double(char *str, int pos);


/* Matrix */
double		**m_init(int m_len);
int			m_len(double **matrix);
double		**m_mult(double **u, double **v);
t_vector	mv_mult(double **u, t_vector v);
int			m_compare(double **u, double **v);
double		**m_identity(double **u);
double		**m_transpose(double **u);
double		m_determinant(double **u);
double		m_minor(double **u, int row, int column);
double		m_cofactor(double **u, int row, int column);
double		**m_inverse(double **matrix);
double		**m_translate(t_vector translation);
double		**m_scale(t_vector scale);
double		**m_rotation(t_vector axis, double angle);
t_vector	m_reflect(t_vector normal);

/* Intersections */
t_vector	ray_position(t_ray *ray, double t);
t_ray	ray_transform(t_ray *ray, double **matrix);
void	plane_intersect(t_object *pl, t_ray *ray, t_intersections *intersection, double num_denom[2]);
void	sphere_intersect(t_object *sp, t_ray *ray, t_intersections *intersection);
void	cylinder_intersect(t_object *cy, t_ray *ray, t_intersections *intersection);
void	object_intersection(t_object *objects, t_ray *ray, t_intersections	*intersection);


void	set_intersections_cy(double t1, double t2, t_intersections *intersections);
double	set_intersections(double t1, double t2);

/* Free Memory */
void		free_data(t_data *data);
void		free_double_pointer(char **double_pointer);
void		free_matrix(double **matrix);
void		free_objects(t_object *objects);
void		free_input(t_input *input);

/* Rendering */
void			render_scene(t_data *data);
void			my_mlx_pixel_put(t_graphics *img, int x, int y, int color);

/* Light */
t_vector 	l_reflect(t_vector light_in, t_vector normal_vector);
int	calculate_lighting(t_data *data, t_intersections *intersection, t_vector normal, bool in_shadow);
t_vector	normal_at(t_intersections *intersection, t_ray *ray);
bool		shadow_at_intersection(t_data *data, t_intersections *intersection,  t_ray *ray);

/* Viewport */
double		pixel_map_x(int x, t_viewport *viewport);
double		pixel_map_y(int y, t_viewport *viewport);
void		prepare_ray(t_data *data, double viewport_x, double viewport_y, t_ray *ray);

/* Color Utils */
t_color_mlx		rgb_to_colour(t_color rgb);


/*debug utils*/
//need to delete later
void			vec_print(t_vector vec);
void			color_print(t_color color);
void		 print_input(const t_input *input);
void 			print_matrix(double **matrix);


#endif
