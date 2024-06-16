/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 19:29:11 by jkaller           #+#    #+#             */
/*   Updated: 2024/06/16 20:18:36 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

t_color	c_add(t_color u, t_color v)
{
	t_color	w;

	w.r = u.r + v.r;
	w.g = u.g + v.g;
	w.b = u.b + v.b;
	return (w);
}

t_color	c_sub(t_color u, t_color v)
{
	t_color	w;

	w.r = u.r - v.r;
	w.g = u.g - v.g;
	w.b = u.b - v.b;
	return (w);
}

t_color	c_mult(t_color u, t_color v)
{
	t_color	w;

	w.r = u.r * v.r;
	w.g = u.g * v.g;
	w.b = u.b * v.b;
	return (w);
}

t_color	c_scalar(t_color u, double t)
{
	u.r *= t;
	u.g *= t;
	u.b *= t;
	return (u);
}

int	rgb_to_colour(t_color rgb)
{
	return (*(int *)(unsigned char [4]){rgb.b, rgb.g, rgb.r, 255});
}
