/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 18:54:51 by ecarlier          #+#    #+#             */
/*   Updated: 2024/05/31 16:24:52 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*CAN DELETE LATER*/

#include "../../include/miniRT.h"

void	vec_print(t_vector vec)
{
	printf("Vec: (x, y, z, w) = (%.4lf, %.4lf, %.4lf, %.4lf)\n", vec.x, vec.y, vec.z, vec.w);
}
