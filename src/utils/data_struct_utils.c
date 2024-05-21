/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_struct_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 23:20:16 by jkaller           #+#    #+#             */
/*   Updated: 2024/05/21 23:41:48 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

int	get_config_len(char *file_path)
{
	int		fd;
	int		config_len;
	char	*line;

	config_len = 0;
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		error_message("Error: File does not exist.\n");
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (ft_strcmp(line, "\n") != 0 && line[0] != '#')
			config_len++;
		free(line);
	}
	close(fd);
	return (config_len);
}
