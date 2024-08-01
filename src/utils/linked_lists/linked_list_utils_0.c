/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_utils_0.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 00:23:57 by jkaller           #+#    #+#             */
/*   Updated: 2024/08/01 20:51:25 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

t_object	*ft_lstnew_object(t_data *data, char *str)
{
	t_object	*object;
	char		*token;
	char		*tmp;
	char		*save_pointer;

	tmp = ft_strdup(str);
	token = ft_strtok_r(tmp, " ", &save_pointer);
	object = NULL;
	if (ft_strncmp(token, "sp", 2) == 0)
		object = add_sphere(data, object, save_pointer);
	else if (ft_strncmp(token, "pl", 2) == 0)
		object = add_plane(data, object, save_pointer);
	else if (ft_strncmp(token, "cy", 2) == 0)
		object = add_cylinder(data, object, save_pointer);
	else
		error_free_data(data, "Error: Invalid object type.\n");
	object->next = NULL;
	free(tmp);
	return (object);
}

void	ft_lstadd_back_minirt(t_object **lst, t_object *new)
{
	t_object	*last;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next != NULL)
		last = last->next;
	last->next = new;
}
