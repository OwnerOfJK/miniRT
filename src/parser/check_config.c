/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 23:03:02 by jkaller           #+#    #+#             */
/*   Updated: 2024/08/01 22:25:45 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

char	*remove_spaces(char *line)
{
	int	i;
	int	write;
	int	space_seen;

	i = 0;
	write = 0;
	space_seen = 0;
	while (line[i])
	{
		if (ft_isspace(line[i]))
			space_seen = 1;
		else
		{
			if (space_seen && !ft_isspace(line[i]))
				line[write++] = ' ';
			line[write++] = line[i];
			space_seen = 0;
		}
		i++;
	}
	line[write] = '\0';
	return (line);
}

char	**parse_to_double_pointer(t_data *data, int fd, int config_len)
{
	char	*line;
	char	**object_configs;
	int		line_count;

	line = NULL;
	line_count = 0;
	object_configs = malloc(sizeof(char *) * (config_len + 1));
	if (object_configs == NULL)
		error_free_data(data, "Error: Memory allocation failed.\n");
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (ft_strcmp(line, "\n") != 0 && line[0] != '#')
		{
			if (ft_strlen(line) > 0 && line[ft_strlen(line) - 1] == '\n')
				line[ft_strlen(line) - 1] = '\0';
			object_configs[line_count++] = remove_spaces(line);
		}
		else
			free(line);
	}
	object_configs[line_count] = NULL;
	return (object_configs);
}

void	check_file_type(t_data *data, char *file_path)
{
	int	i;
	int	path_len;

	path_len = ft_strlen(file_path);
	i = path_len;
	while (i != 0 && file_path[i] != '.')
		i--;
	if (ft_strncmp(&file_path[i], ".rt", 3) != 0)
		error_free_data(data, "Error: Wrong file type.\n");
}

void	check_config(t_data *data, char *file_path, int config_len)
{
	int		fd;

	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		error_free_data(data, "Error: File does not exist.\n");
	check_file_type(data, file_path);
	data->object_configs = parse_to_double_pointer(data, fd, config_len);
	close(fd);
	check_information(data, data->object_configs);
}

void	check_information(t_data *data, char **object_configs)
{
	int	i;
	int	variable_count;

	i = 0;
	variable_count = 0;
	while (object_configs[i])
	{
		if (object_configs[i][0] == 'A'
			|| object_configs[i][0] == 'C' || object_configs[i][0] == 'L')
			variable_count++;
		i++;
	}
	if (variable_count != 3)
		error_free_data(data, "Error: Missing or too many A, \
			C or L elements.\n");
}
