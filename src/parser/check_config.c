/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 23:03:02 by jkaller           #+#    #+#             */
/*   Updated: 2024/05/26 16:42:52 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

char	*remove_spaces(char *line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i] != '\0')
	{
		if (line[i] != ' ')
		{
			line[j] = line[i];
			j++;
		}
		i++;
	}
	line[j] = '\0';
	return (line);
}

char	**parse_to_double_pointer(int fd, int config_len)
{
	char	*line;
	char	**object_configs;
	int		line_count;

	line = NULL;
	line_count = 0;
	object_configs = malloc(sizeof(char *) * (config_len + 1));
	if (object_configs == NULL)
		error_message("Error: Memory allocation failed.\n");
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (ft_strcmp(line, "\n") != 0 && line[0] != '#')
		{
			line[ft_strlen(line) - 1] = '\0';
			object_configs[line_count++] = remove_spaces(line);
		}
		else
			free(line);
	}
	object_configs[line_count] = NULL;
	return (object_configs);
}

void	check_file_type(char *file_path)
{
	int	i;
	int	path_len;

	path_len = ft_strlen(file_path);
	i = path_len;
	while (i != 0 && file_path[i] != '.')
		i--;
	if (ft_strncmp(&file_path[i], ".rt", 3) != 0)
		error_message("Error: Wrong file type.\n");
}

char	**check_config(char *file_path)
{
	int		fd;
	char	**object_configs;
	int		config_len;

	object_configs = NULL;
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		error_message("Error: File does not exist.\n");
	check_file_type(file_path);
	config_len = get_config_len(file_path);
	object_configs = parse_to_double_pointer(fd, config_len);
	check_information(object_configs); //this is next
	close(fd);
	return (object_configs);
}
