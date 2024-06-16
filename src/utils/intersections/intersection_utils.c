/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 20:43:09 by jkaller           #+#    #+#             */
/*   Updated: 2024/06/16 18:03:02 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

/*
Computes a colour in format trgb for mlx library
*/
t_color_mlx	rgb_to_colour(t_color rgb)
{
	return (*(int *)(unsigned char [4]){rgb.b, rgb.g, rgb.r, 255});
}

// void static print_sphere(t_sphere *sphere) {
//         printf("Sphere\n");
//         printf("Position: %f %f %f\n", sphere->pos.x, sphere->pos.y, sphere->pos.z);
//         printf("Diameter: %f\n", sphere->diameter);
//         printf("Color: %f %f %f\n", sphere->color.r, sphere->color.g, sphere->color.b);
//        // sphere = (t_sphere *)sphere->base.next;
//     	printf("\n");
// }

t_intersections	spheres_inter(t_sphere *sp, t_ray *ray)
{
	t_intersections	intersect;
	t_intersections	temp;

	intersect.hit = 0;
	temp.t1 = DBL_MAX;
	while(sp!= NULL)
	{
		//print_sphere(sp);
		intersect = sphere_intersections(sp, ray);

		if (intersect.count != 0)
		{
			intersect.hit = 1;
			if (intersect.t1 < temp.t1)
				temp = intersect;
		}
		sp = (t_sphere *)sp->base.next;
	}
	if (intersect.hit == 1)
		return (intersect);
	else
		return (temp);
}
void	set_intersections(double t1, double t2, t_intersections *intersections)
{
	double	temp;

	temp = 0;
	if (t1 > EPSILON && t2 > EPSILON)
	{
		if (t1 > t2)
		{
			temp = t1;
			t1 = t2;
			t2 = temp;
		}
		intersections->t1 = t1;
		intersections->t2 = t2;
		intersections->count = 2;
	}
	else if (t1 > EPSILON)
	{
		intersections->t1 = t1;
		intersections->count = 1;
	}
	else if (t2 > EPSILON)
	{
		intersections->t1 = t2;
		intersections->count = 1;
	}
}



t_intersections	sphere_intersections(t_sphere *sp, t_ray *ray)
{
	t_intersections	intersections;
	t_equat2		equat2;
	t_vector		sphere_to_ray;
	double			radius;
	double			delta;

	radius = (sp->diameter / 2);
	sphere_to_ray = v_sub(ray->origin, sp->pos);
	equat2.a = v_dot(ray->direction, ray->direction);
	equat2.b = 2.0 * v_dot(ray->direction, sphere_to_ray);
	equat2.c = v_dot(sphere_to_ray, sphere_to_ray) - (radius * radius);
	delta = solve_quadratic(&equat2);
	intersections.count = 0;
	if (delta >= 0)
	{
		set_intersections(equat2.t1, equat2.t2, &intersections);
		intersections.color = sp->color;
	}

	else
		intersections.count = 0;
	return (intersections);
}
