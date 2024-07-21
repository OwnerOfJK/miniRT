/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 00:23:57 by jkaller           #+#    #+#             */
/*   Updated: 2024/07/21 15:25:25 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

t_object	*ft_lstnew_object(char *str)
{
	t_object	*object;
	char		*token;
	char		*tmp;
	char		*save_pointer;

	tmp = ft_strdup(str);
	token = ft_strtok_r(tmp, " ", &save_pointer);
	object = NULL;
	if (ft_strncmp(token, "sp", 2) == 0)
		object = add_sphere(object, save_pointer);
	else if (ft_strncmp(token, "pl", 2) == 0)
		object = add_plane(object, save_pointer);
	else if (ft_strncmp(token, "cy", 2) == 0)
		object = add_cylinder(object, save_pointer);
	else
	{
		printf("token: %s\n", token);
		error_message("Error: Invalid object type.\n");
	}
	object->next = NULL;
	free(tmp);
	return (object);
}

t_object	*add_sphere(t_object *object, char *save_pointer)
{
	char		*token;

	object = malloc(sizeof(t_object));
	if (object == NULL)
		error_message("Error: Memory allocation failed.\n");
	object->type = SPHERE;
	token = ft_strtok_r(NULL, " ", &save_pointer);
	if (token != NULL)
		object->pos = parse_coordinate(token);
	token = ft_strtok_r(NULL, " ", &save_pointer);
	if (token != NULL)
		object->shape.sphere.diameter = ft_atod(token);
	token = ft_strtok_r(NULL, " ", &save_pointer);
	if (token != NULL)
		object->color = parse_color(token);
	object->transformation_matrix = m_translate(object->pos);
	object->inverse_matrix = m_inverse(object->transformation_matrix);
	return (object);
}

t_object	*add_plane(t_object *object, char *save_pointer)
{
	char		*token;

	object = malloc(sizeof(t_object));
	if (object == NULL)
		error_message("Error: Memory allocation failed.\n");
	object->type = PLANE;
	token = ft_strtok_r(NULL, " ", &save_pointer);
	if (token != NULL)
		object->pos = parse_coordinate(token);
	token = ft_strtok_r(NULL, " ", &save_pointer);
	if (token != NULL)
		object->shape.plane.normal_vector = parse_vector(token);
	token = ft_strtok_r(NULL, " ", &save_pointer);
	if (token != NULL)
		object->color = parse_color(token);
	object->transformation_matrix = m_translate(object->pos);
	object->inverse_matrix = m_inverse(object->transformation_matrix);
	return (object);
}

t_object	*add_cylinder(t_object *object, char *save_pointer)
{
	char		*token;

	object = malloc(sizeof(t_object));
	if (object == NULL)
		error_message("Error: Memory allocation failed.\n");
	object->type = CYLINDER;
	token = ft_strtok_r(NULL, " ", &save_pointer);
	if (token != NULL)
		object->pos = parse_coordinate(token);
	token = ft_strtok_r(NULL, " ", &save_pointer);
	if (token != NULL)
		object->shape.cylinder.axis_vector = parse_vector(token);
	token = ft_strtok_r(NULL, " ", &save_pointer);
	if (token != NULL)
		object->shape.cylinder.diameter = ft_atod(token);
	token = ft_strtok_r(NULL, " ", &save_pointer);
	if (token != NULL)
		object->shape.cylinder.height = ft_atod(token);
	token = ft_strtok_r(NULL, " ", &save_pointer);
	if (token != NULL)
		object->color = parse_color(token);
	object->transformation_matrix = m_translate(object->pos);
	object->inverse_matrix = m_inverse(object->transformation_matrix);
	object->shape.cylinder.cap_up = v_add(object->pos, v_scalar(object->shape.cylinder.axis_vector, object->shape.cylinder.height / 2.0));
	object->shape.cylinder.cap_down = v_add(object->pos, v_scalar(object->shape.cylinder.axis_vector, -object->shape.cylinder.height / 2.0));
	return (object);
}

void	ft_lstadd_back_miniRT(t_object **lst, t_object *new)
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
