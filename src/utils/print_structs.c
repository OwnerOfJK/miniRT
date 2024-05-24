/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_structs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 23:13:40 by jkaller           #+#    #+#             */
/*   Updated: 2024/05/24 18:54:42 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	print_double_pointer(char **double_pointer)
{
	int	i;

	i = 0;
	while (double_pointer[i] != NULL)
	{
		ft_printf("%s\n", double_pointer[i]);
		i++;
	}
}
