/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 19:25:21 by ecarlier          #+#    #+#             */
/*   Updated: 2024/07/09 13:06:56 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

/*
	Normalizes a vector
*/
t_vector	v_normalize(t_vector v)
{
	double	length;

	length = v_length(v);
	// if (v.w == 1)
	// 	ft_putstr_fd("v_normalize: Why are you normalizing a point?\n", 2);
	if (length)
	{
		v.x /= length;
		v.y /= length;
		v.z /= length;
	}
	return (v);
}
t_vector	neg(t_vector u)
{
	return (v_scalar(u, -1.0));
}
