/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 20:43:09 by jkaller           #+#    #+#             */
/*   Updated: 2024/06/16 18:21:24 by ecarlier         ###   ########.fr       */
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



/*

Need to create a function to go through all the shapes
*/
