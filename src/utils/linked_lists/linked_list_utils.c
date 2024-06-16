/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 00:23:57 by jkaller           #+#    #+#             */
/*   Updated: 2024/06/16 16:45:30 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

t_sphere	*ft_lstnew_sphere(char *str)
{
	t_sphere	*sphere;
	char		*token;
	char		*tmp;
	char		*save_pointer;

	sphere = malloc(sizeof(t_sphere));
	if (sphere == NULL)
		error_message("Error: Memory allocation failed.\n");
	tmp = ft_strdup(str);
	token = ft_strtok_r(tmp, " ", &save_pointer);
	token = ft_strtok_r(NULL, " ", &save_pointer);
	if (token != NULL)
		sphere->pos = parse_coordinate(token);
	token = ft_strtok_r(NULL, " ", &save_pointer);
	if (token != NULL)
		sphere->diameter = ft_atod(token);
	token = ft_strtok_r(NULL, " ", &save_pointer);
	if (token != NULL)
		sphere->color = parse_color(token);
	sphere->base.next = NULL;
	free(tmp);
	return (sphere);
}

t_plane	*ft_lstnew_plane(char *str)
{
	t_plane		*plane;
	char		*token;
	char		*tmp;
	char		*save_pointer;

	plane = malloc(sizeof(t_plane));
	if (plane == NULL)
		error_message("Error: Memory allocation failed.\n");
	tmp = ft_strdup(str);
	token = ft_strtok_r(tmp, " ", &save_pointer);
	token = ft_strtok_r(NULL, " ", &save_pointer);
	if (token != NULL)
		plane->pos = parse_coordinate(token);
	token = ft_strtok_r(NULL, " ", &save_pointer);
	if (token != NULL)
		plane->normal_vector = parse_vector(token);
	token = ft_strtok_r(NULL, " ", &save_pointer);
	if (token != NULL)
		plane->color = parse_color(token);
	plane->base.next = NULL;
	free(tmp);
	return (plane);
}

t_cylinder	*ft_lstnew_cylinder(char *str)
{
	t_cylinder		*cylinder;
	char		*token;
	char		*tmp;
	char		*save_pointer;

	cylinder = malloc(sizeof(t_cylinder));
	if (cylinder == NULL)
		error_message("Error: Memory allocation failed.\n");
	tmp = ft_strdup(str);
	token = ft_strtok_r(tmp, " ", &save_pointer);
	token = ft_strtok_r(NULL, " ", &save_pointer);
	if (token != NULL)
		cylinder->pos = parse_coordinate(token);
	token = ft_strtok_r(NULL, " ", &save_pointer);
	if (token != NULL)
		cylinder->axis_vector = parse_vector(token);
	token = ft_strtok_r(NULL, " ", &save_pointer);
	if (token != NULL)
		cylinder->diameter = ft_atod(token);
	token = ft_strtok_r(NULL, " ", &save_pointer);
	if (token != NULL)
		cylinder->height = ft_atod(token);
	if (token != NULL)
		cylinder->color = parse_color(token);
	cylinder->base.next = NULL;
	free(tmp);
	return (cylinder);
}

void	ft_lstadd_back_miniRT(t_base_node **lst, t_base_node *new)
{
	t_base_node	*last;

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
