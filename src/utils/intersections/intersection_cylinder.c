/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_cylinder.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 16:45:49 by ecarlier          #+#    #+#             */
/*   Updated: 2024/06/20 13:34:34 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

t_intersections	cylinder_intersections(t_cylinder *cy, t_ray *ray)
{
	t_intersections	intersections;
	t_equat2		equat;
	t_vector		cylinder_to_ray;
	double			radius;
	double			delta;

	//intersections.count = 0;
    if (cy == NULL || ray == NULL) {
        printf("Error: NULL pointer passed to cylinder_intersections\n");
        //return intersections;
    }

	radius = cy->diameter / 2;
	cylinder_to_ray = v_sub(ray->origin, cy->cap_down);
	//equat.a = v_dot(ray->direction, ray->direction) - ((v_dot(ray->direction, cy->axis_vector) * (v_dot(ray->direction, cy->axis_vector))));
//	equat.b = 2 * (v_dot(ray->direction, cylinder_to_ray) - (v_dot(ray->direction, cy->axis_vector) * v_dot(ray->direction, cy->axis_vector))
//);
	//equat.c = v_dot(cylinder_to_ray, cylinder_to_ray) - (v_dot(cylinder_to_ray, cy->axis_vector) * v_dot(cylinder_to_ray, cy->axis_vector) - (radius * radius));
  	equat.a = v_dot(ray->direction, ray->direction) - (v_dot(ray->direction, cy->axis_vector) * v_dot(ray->direction, cy->axis_vector));
    equat.b = 2 * (v_dot(ray->direction, cylinder_to_ray) - (v_dot(ray->direction, cy->axis_vector) * v_dot(cylinder_to_ray, cy->axis_vector)));
	equat.c = v_dot(cylinder_to_ray, cylinder_to_ray) - (v_dot(cylinder_to_ray, cy->axis_vector) * v_dot(cylinder_to_ray, cy->axis_vector)) - (radius * radius);
	// double dv = v_dot(ray->direction, cy->axis_vector);
    // double cv = v_dot(cylinder_to_ray, cy->axis_vector);

    // equat.a = v_dot(ray->direction, ray->direction) - dv * dv;
    // equat.b = 2 * (v_dot(ray->direction, cylinder_to_ray) - dv * cv);
    // equat.c = v_dot(cylinder_to_ray, cylinder_to_ray) - cv * cv - radius * radius;

    printf("cylinder_to_ray: (%f, %f, %f, %f)\n", cylinder_to_ray.x, cylinder_to_ray.y, cylinder_to_ray.z, cylinder_to_ray.w);
  //  printf("dv: %f, cv: %f\n", dv, cv);


	delta = solve_quadratic(&equat);

	printf("delta: %f\n", delta);
    printf("equat.a: %f, equat.b: %f, equat.c: %f\n", equat.a, equat.b, equat.c);
    printf("t1: %f, t2: %f\n", equat.t1, equat.t2);
	//intersections.count = 0;
	if (delta >= 0)
	{
		set_intersections(equat.t1, equat.t2, &intersections);
		intersections.color = cy->color;
	}
	else
		intersections.count = 0;

	return (intersections);
}
