/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 20:23:55 by ecarlier          #+#    #+#             */
/*   Updated: 2024/05/31 17:23:52 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

/*
	Checks if two vectors are equal
*/
int	v_compare(t_vector u, t_vector v)
{
	if (u.w != v.w)
		ft_putstr_fd("v_compare: Why are you comparing points with vectors?\n", 2);
	return (u.x == v.x && u.y == v.y && u.z == v.z);
}

/*
	Generates a vector with param x, y and z
*/
t_vector	v_init(double x, double y, double z, double w)
{
	t_vector	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	vec.w = w;
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
	if (u.w == 1 || v.w == 1)
		ft_putstr_fd("v_dot: Why are you cross multiplying points?\n", 2);
	return (w);
}

/*
	inverts the vector u
	return -n (-x, -y, -z)
*/
t_vector	v_neg(t_vector u)
{
	if (u.w == 1)
		ft_putstr_fd("v_neg: Why are you negating a point?\n", 2);
	return (v_scalar(u, -1.0));
}

/*
	return the lenght of the vector v
*/
double	v_length(t_vector v)
{
	if (v.w == 1)
		ft_putstr_fd("v_length: Why are you \
		calculating the length of a point?\n", 2);
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}
