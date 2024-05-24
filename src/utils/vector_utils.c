/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 18:46:59 by ecarlier          #+#    #+#             */
/*   Updated: 2024/05/24 19:08:59 by ecarlier         ###   ########.fr       */
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
	return (w);
}

/*
	dot product of two vectors u and v
	(u · v)
*/
double	v_dot(t_vector u, t_vector v)
{
	return (u.x * v.x + u.y * v.y + u.z * v.z);
}
