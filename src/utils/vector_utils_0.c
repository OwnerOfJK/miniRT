/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils_0.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 18:46:59 by ecarlier          #+#    #+#             */
/*   Updated: 2024/05/31 16:46:43 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

/*
	addition of two vectors u and v
	(u + v)
*/
t_vector	v_add(t_vector u, t_vector v)
{
	t_vector	w;

	w.x = u.x + v.x;
	w.y = u.y + v.y;
	w.z = u.z + v.z;
	w.w = u.w + v.w;
	if (w.w > 1)
		ft_putstr_fd("Warning: w value is greater than 1\n", 2);
	return (w);
}

/*
	subtraction of two vectors u and v
	(u - v)
*/
t_vector	v_sub(t_vector u, t_vector v)
{
	t_vector	w;

	w.x = u.x - v.x;
	w.y = u.y - v.y;
	w.z = u.z - v.z;
	w.w = u.w - v.w;
	if (w.w < 0)
		ft_putstr_fd("Warning: w value is lower than 0\n", 2);
	return (w);
}

/*
	multiplication of two vectors u and v
	(u * w)
*/
t_vector	v_mult(t_vector u, t_vector v)
{
	t_vector	w;

	w.x = u.x * v.x;
	w.y = u.y * v.y;
	w.z = u.z * v.z;
	if (u.w == 1 || v.w == 1)
		ft_putstr_fd("v_mult: Why are you multiplying points?\n", 2);
	return (w);
}

/*
	dot product of two vectors u and v
	(u · v)
*/
double	v_dot(t_vector u, t_vector v)
{
	if (u.w == 1 || v.w == 1)
		ft_putstr_fd("v_dot: Why are you dot multiplying points?\n", 2);
	return (u.x * v.x + u.y * v.y + u.z * v.z);
}

/*
	multiplication of a vector and a scalar
	(t * v)
*/
t_vector	v_scalar(t_vector u, double t)
{
	u.x *= t;
	u.y *= t;
	u.z *= t;
	if (u.w == 1)
		ft_putstr_fd("v_scalar: Why are you multiplying a point?\n", 2);
	return (u);
}
