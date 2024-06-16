/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number_conversion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:55:19 by jkaller           #+#    #+#             */
/*   Updated: 2024/06/16 16:45:40 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

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

t_color	parse_color(char *str)
{
	t_color	*color;
	char	*token;
	char	*tmp;
	char	*save_pointer;

	color = malloc(sizeof(t_color));
	if (color == NULL)
		error_message("Error: Memory allocation failed.\n");
	tmp = ft_strdup(str);
	token = ft_strtok_r(tmp, ",", &save_pointer);
	if (token != NULL)
		color->r = ft_atod(token);
	token = ft_strtok_r(NULL, ",", &save_pointer);
	if (token != NULL)
		color->g = ft_atod(token);
	token = ft_strtok_r(NULL, ",", &save_pointer);
	if (token != NULL)
		color->b = ft_atod(token);
	free(tmp);
	return (*color);
}

t_vector	parse_coordinate(char *str)
{
	t_vector	*coordinate;
	char		*token;
	char		*tmp;
	char		*save_pointer;

	coordinate = malloc(sizeof(t_vector));
	if (coordinate == NULL)
		error_message("Error: Memory allocation failed.\n");
	tmp = ft_strdup(str);
	token = ft_strtok_r(tmp, ",", &save_pointer);
	if (token != NULL)
		coordinate->x = ft_atod(token);
	token = ft_strtok_r(NULL, ",", &save_pointer);
	if (token != NULL)
		coordinate->y = ft_atod(token);
	token = ft_strtok_r(NULL, ",", &save_pointer);
	if (token != NULL)
		coordinate->z = ft_atod(token);
	coordinate->w = 1;
	free(tmp);
	return (*coordinate);
}

t_vector	parse_vector(char *str)
{
	t_vector	*vector;
	char		*token;
	char		*tmp;
	char		*save_pointer;

	vector = malloc(sizeof(t_vector));
	if (vector == NULL)
		error_message("Error: Memory allocation failed.\n");
	tmp = ft_strdup(str);
	token = ft_strtok_r(tmp, ",", &save_pointer);
	if (token != NULL)
		vector->x = ft_atod(token);
	token = ft_strtok_r(NULL, ",", &save_pointer);
	if (token != NULL)
		vector->y = ft_atod(token);
	token = ft_strtok_r(NULL, ",", &save_pointer);
	if (token != NULL)
		vector->z = ft_atod(token);
	vector->w = 0;
	free(tmp);
	return (*vector);
}
