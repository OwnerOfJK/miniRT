/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number_conversion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:55:19 by jkaller           #+#    #+#             */
/*   Updated: 2024/05/27 20:27:46 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

char	*find_and_extract_double(char *str, int pos)
{
	char	*double_value;
	int		i;
	int		count;

	double_value = malloc(sizeof(char) * 4);
	i = 0;
	count = 0;
	while (str[i] != '.' && str[i] != '\0')
	{
		i++;
		if (str[i] == '.')
		{
			count++;
			if (count < pos)
				i++;
		}
	}
	double_value = ft_strncpy(double_value, &str[i - 1], 3);
	return (double_value);
}
