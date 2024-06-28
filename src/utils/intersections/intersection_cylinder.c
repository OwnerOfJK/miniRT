// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   intersection_cylinder.c                            :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/06/17 16:45:49 by ecarlier          #+#    #+#             */
// /*   Updated: 2024/06/21 12:45:00 by ecarlier         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "../../../include/miniRT.h"

t_intersections	cylinder_inter(t_cylinder *cy, t_ray *ray)
{
	t_intersections	intersect;
	t_intersections	temp;

	temp.hit = 0;
	intersect.hit = 0;
	temp.t1 = DBL_MAX; //not sure about this
	while (cy != NULL)
	{
		intersect = cylinder_intersections(cy, ray);
		if (intersect.count != 0)
		{
			intersect.hit = 1;
			if (intersect.t1 < temp.t1)
				temp = intersect;
		}
		cy = (t_cylinder *)cy->base.next;
	}
	if (intersect.hit == 1)
		return (intersect);
	else
		return (temp);
}

// // double	cap_inter(t_cylinder *cy, t_ray *ray, t_vector cap)
// // {
// // 	t_plane	*plane;
// // 	t_intersections	inter;
// // 	plane = create_plane(cap, cy->axis_vector, BLACK);
// // 	inter = plane_intersect(plane, ray);
// // 	if (inter.t1 > EPSILON)
// // 		return (inter.t1);
// // 	return (-1);
// // }
// // //t_intersections	plane_intersect(t_plane *pl, t_ray *ray)

// // double	verify_t(t_cylinder *cy, t_ray *ray, t_intersections *inter)
// // {
// // 	double t;
// // 	double t3;
// // 	double t4;

// // 	t = inter->t1;
// // 	t3 = cap_inter(cy, ray, cy->cap_down);
// // 	t4 = cap_inter(cy, ray, cy->cap_up);
// // 	inter->t1 = INFINITY;

// // }


t_intersections	cylinder_intersections(t_cylinder *cy, t_ray *ray)
{
	t_intersections	intersections;
	t_equat2		equat;
	t_vector		cylinder_to_ray;
	double			radius;
	double			delta;

	double			y0;
	double			y1;



	//intersections.count = 0;
	radius = cy->diameter / 2;
	cylinder_to_ray = v_sub(ray->origin, cy->cap_down);
  	equat.a = v_dot(ray->direction, ray->direction) - (v_dot(ray->direction, cy->axis_vector) * v_dot(ray->direction, cy->axis_vector));
    equat.b = 2 * (v_dot(ray->direction, cylinder_to_ray) - (v_dot(ray->direction, cy->axis_vector) * v_dot(cylinder_to_ray, cy->axis_vector)));
	equat.c = v_dot(cylinder_to_ray, cylinder_to_ray) - (v_dot(cylinder_to_ray, cy->axis_vector) * v_dot(cylinder_to_ray, cy->axis_vector)) - (radius * radius);

   // printf("cylinder_to_ray: (%f, %f, %f, %f)\n", cylinder_to_ray.x, cylinder_to_ray.y, cylinder_to_ray.z, cylinder_to_ray.w);
	delta = solve_quadratic(&equat);

	// printf("delta: %f\n", delta);
    // printf("equat.a: %f, equat.b: %f, equat.c: %f\n", equat.a, equat.b, equat.c);
    // printf("t1: %f, t2: %f\n", equat.t1, equat.t2);
	//intersections.count = 0;

	if (delta >= 0)
	{
		set_intersections(equat.t1, equat.t2, &intersections);
		y0 = v_dot(ray->direction, cy->axis_vector) * equat.t1 + v_dot(cylinder_to_ray, cy->axis_vector);
		y1 = v_dot(ray->direction, cy->axis_vector) * equat.t2 + v_dot(cylinder_to_ray, cy->axis_vector);
		if (y0 >= cy->height / - 2 && y0 <= cy->height / 2 )
		{
			intersections.color = cy->color;
		}
		else if ( y1 >= cy->height / - 2 && y1 <= cy->height / 2 )
		{
			intersections.color = cy->color;
		}
		else
			intersections.count = 0;
	}
	else
		intersections.count = 0;

	return (intersections);
}

// t_intersections	cylinder_intersections(t_cylinder *cy, t_ray ray)
// {
// 	t_intersections	intersections;
// 	t_equat2		d;

// 	double			delta;
// 	d.a = pow(ray.direction.x, 2) + pow(ray.direction.z, 2);
// 	d.b = (2.0 * ray.origin.x * ray.direction.x) + (2.0 * ray.origin.z * ray.direction.z);
// 	d.c = pow(ray.origin.x, 2) + pow(ray.origin.z, 2) - 1.0;
// 	delta = solve_quadratic(&d);

// 	// printf("delta: %f\n", delta);
//     // printf("equat.a: %f, equat.b: %f, equat.c: %f\n", equat.a, equat.b, equat.c);
//     // printf("t1: %f, t2: %f\n", equat.t1, equat.t2);
// 	//intersections.count = 0;
// 	if (delta >= 0)
// 	{
// 		set_intersections(d.t1, d.t2, &intersections);
// 		verify_t(cy, ray, &intersections);
// 		intersections.color = cy->color;
// 	}
// 	else
// 		intersections.count = 0;

// 	return (intersections);
// }

// //  void verify_t(t_cylinder *cy, t_ray ray, t_intersections *d)
// // {
// // 	double y0;
// // 	double y1;
// // 	double min;
// // 	double max;
// // 	double temp;

// // 	min = cy->pos.y - (cy->height / 2.0);
// // 	max = cy->pos.y + (cy->height / 2.0);


// // 	y0 = ray.origin.y + d->t1 * ray.direction.y;
// // 	y1 = ray.origin.y + d->t2 * ray.direction.y;

// // 	if (min > y0 && y0 < max)
// // 	{
// // 			temp = d->t1;
// // 			d->t1 = d->t2;
// // 			d->t2 = temp;
// // 	}
// // 	if (min > y0 && y0 < max)
// // 	{
// // 			temp = d->t1;
// // 			d->t1 = d->t2;
// // 			d->t2 = temp;
// // 	}
// // }



// bool check_caps(t_cylinder *cy, t_vector cap, t_intersections *inter, double t) {
//     double len;
//     t_vector point;

//     point = ray_at(&inter->ray, t);
//     len = vec3_length(vec3_sub(point, cap));
//     len += EPSILON;
//     if (len <= cy->diameter / 2.0 && t > EPSILON && t < inter->t1) {
//         inter->t1 = t;
//         inter->color = cy->color;
//         return true;
//     }
//     return false;
// }

// bool check_caps(t_cylinder *cy, t_vector cap, t_intersections *inter, double t) {
//     double len;
//     t_vector point;

//     point = ray_at(&inter->ray, t);
//     len = vec3_length(vec3_sub(point, cap));
//     len += EPSILON;
//     if (len <= cy->diameter / 2.0 && t > EPSILON && t < inter->t1) {
//         inter->t1 = t;
//         inter->color = cy->color;
//         return true;
//     }
//     return false;
// }

// bool check_walls(t_cylinder *cy, t_intersections *inter, double t) {
//     t_vector point;
//     t_vector co;
//     t_vector a;
//     double m;
//     double len;

//     point = ray_at(&inter->ray, t);
//     co = vec3_sub(inter->ray.origin, cy->cap_down);
//     m = vec3_dot(inter->ray.direction, cy->axis_vector) * t + vec3_dot(co, cy->axis_vector);
//     a = vec3_add(cy->cap_down, vec3_scale(cy->axis_vector, m));
//     len = vec3_length(vec3_sub(point, a));
//     m -= EPSILON;
//     len -= EPSILON;
//     if (m >= 0 && m <= cy->height && len <= cy->diameter / 2.0 && t > EPSILON && t < inter->t1) {
//         inter->t1 = t;
//         inter->color = cy->color;
//         return true;
//     }
//     return false;
// }
// double cap_intersection(t_cylinder *cy, t_ray *ray, t_vector cap) {
//     t_plane plane;
//     t_intersections inter;

//     // Remplacer `plane_from_numbers` et `plane_intersect` par vos fonctions spécifiques
//     plane = plane_from_numbers(cap, cy->axis_vector, cy->color);
//     if (plane_intersect(&plane, ray, &inter)) {
//         return inter.t1;
//     }
//     return -1;
// }

// double verify_intersections(t_cylinder *cy, t_ray *ray, t_equation *equation, t_intersections *inter) {
//     double t3, t4;

//     t3 = cap_intersection(cy, ray, cy->cap_down);
//     t4 = cap_intersection(cy, ray, cy->cap_up);
//     inter->t1 = INFINITY;
//     inter->ray = *ray;
//     check_walls(cy, inter, equation->t1);
//     check_walls(cy, inter, equation->t2);
//     check_caps(cy, cy->cap_down, inter, t3);
//     check_caps(cy, cy->cap_up, inter, t4);
//     if (inter->t1 == INFINITY) {
//         return 0;
//     }
//     return inter->t1;
// }

// bool cylinder_intersect(t_cylinder *cy, t_ray *ray, t_intersections *inter) {
//     t_vector co;
//     t_equat2 equation;

//     equation.t1 = -1;
//     equation.t2 = -1;
//     co = vec3_sub(ray->origin, cy->cap_down);
//     equation.a = vec3_dot(ray->direction, ray->direction) - pow(vec3_dot(ray->direction, cy->axis_vector), 2);
//     equation.b = 2 * (vec3_dot(ray->direction, co) - (vec3_dot(ray->direction, cy->axis_vector) * vec3_dot(co, cy->axis_vector)));
//     equation.c = vec3_dot(co, co) - pow(vec3_dot(co, cy->axis_vector), 2) - pow(cy->diameter / 2.0, 2);
//     solve(&equation);
//     if (equation.t1 <= 0 && equation.t2 <= 0) {
//         return false;
//     }
//     double t = verify_intersections(cy, ray, &equation, inter);
//     if (t > 0.0) {
//         inter->t1 = t;
//         inter->color = cy->color;
//         return true;
//     }
//     return false;
// }

// t_intersections cylinder_inter(t_cylinder *cy, t_ray *ray) {
//     t_intersections intersect;
//     t_intersections temp;

//     temp.hit = 0;
//     intersect.hit = 0;
//     temp.t1 = DBL_MAX;
//     while (cy != NULL) {
//         intersect = cylinder_intersections(cy, ray);
//         if (intersect.count != 0) {
//             intersect.hit = 1;
//             if (intersect.t1 < temp.t1) {
//                 temp = intersect;
//             }
//         }
//         cy = (t_cylinder *)cy->base.next;
//     }
//     if (temp.hit == 1) {
//         return temp;
//     } else {
//         return intersect;
//     }
// }
