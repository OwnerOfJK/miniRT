/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 18:54:51 by ecarlier          #+#    #+#             */
/*   Updated: 2024/05/24 18:56:41 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*CAN DELETE LATER*/

#include "../../include/miniRT.h"

void	vec_print(t_vector vec)
{
	printf("Vec: (x, y, z) = (%.4lf, %.4lf, %.4lf)\n", vec.x, vec.y, vec.z);
}
