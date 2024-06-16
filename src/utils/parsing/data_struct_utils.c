/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_struct_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 23:20:16 by jkaller           #+#    #+#             */
/*   Updated: 2024/06/16 16:45:36 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

int	get_config_len(char *file_path)
{
	int		fd;
	int		config_len;
	char	*line;

	config_len = 0;
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		error_message("Error: File not found.\n");
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (ft_strcmp(line, "\n") != 0 && line[0] != '#')
			config_len++;
		free(line);
	}
	if (config_len == 0)
		error_message("Error: Empty file.\n");
	close(fd);
	return (config_len);
}

char	**find_index(char** object_configs, char *index, int len)
{
	while (*object_configs)
	{
		if (!ft_strncmp(*object_configs, index, len))
			return (object_configs);
		object_configs++;
	}
	return (NULL);
}
