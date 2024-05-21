/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 21:50:43 by jkaller           #+#    #+#             */
/*   Updated: 2024/05/21 21:56:16 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

//this function should also free whatever needs to be freed

void	error_message(char *error_message)
{
	//free stuff
	ft_putstr_fd(error_message, 2);
	exit(EXIT_FAILURE);
}
