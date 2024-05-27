/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number_conversion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:55:19 by jkaller           #+#    #+#             */
/*   Updated: 2024/05/27 21:30:14 by jkaller          ###   ########.fr       */
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

void	parse_rgb(char *str, int i, t_color *color)
{
	char	*token;

	token = ft_strtok(str + i, ",");
	ft_printf("token: %s\n", token);
	if (token != NULL)
		color->r = ft_atod(token);
	token = ft_strtok(NULL, ",");
	ft_printf("token: %s\n", token);
	if (token != NULL)
		color->g = ft_atod(token);
	token = ft_strtok(NULL, ",");
	ft_printf("token: %s\n", token);
	if (token != NULL)
		color->b = ft_atod(token);
}

t_color	*parse_to_color(char *str)
{
	t_color	*color;
	int		i;

	i = ft_strlen(str);
	color = malloc(sizeof(t_color));
	if (color == NULL)
		error_message("Error: Memory allocation failed.\n");
	while (str[i] != ' ')
		i--;
	parse_rgb(str, i + 1, color);
	return (color);
}