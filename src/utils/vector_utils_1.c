/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 20:23:55 by ecarlier          #+#    #+#             */
/*   Updated: 2024/05/24 20:58:11 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

/*
	Checks if two vectors are equal
*/
int	v_compare(t_vector u, t_vector v)
{
	return (u.x == v.x && u.y == v.y && u.z == v.z);
}

/*
	Generates a vector with param x, y and z
*/
t_vector	v_init(double x, double y, double z)
{
	t_vector	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

/*
	cross product of two vectors u and v
	(u X v)
*/
t_vector	v_cross(t_vector u, t_vector v)
{
	t_vector	w;

	w.x = u.y * v.z - u.z * v.y;
	w.y = u.z * v.x - u.x * v.z;
	w.z = u.x * v.y - u.y * v.x;
	return (w);
}

/*
	inverts the vector u
	return -n (-x, -y, -z)
*/
t_vector	v_neg(t_vector u)
{
	return (v_scalar(u, -1.0));
}

/*
	return the lenght of the vector v
*/
double	v_lenght(t_vector v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}
