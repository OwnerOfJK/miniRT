/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 18:54:51 by ecarlier          #+#    #+#             */
/*   Updated: 2024/07/31 21:03:15 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*CAN DELETE LATER*/

#include "../../include/miniRT.h"

void	vec_print(t_vector vec)
{
	printf("Vec: (x, y, z, w) = (%.4lf, %.4lf, %.4lf, %.4lf)\n",
		vec.x, vec.y, vec.z, vec.w);
}

void	color_print(t_color color)
{
	printf("Color: (r, g, b) = (%.4lf, %.4lf, %.4lf)\n",
		color.r, color.g, color.b);
}
