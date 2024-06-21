/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 19:25:21 by ecarlier          #+#    #+#             */
/*   Updated: 2024/06/21 15:41:40 by jkaller          ###   ########.fr       */
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
