/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 00:23:57 by jkaller           #+#    #+#             */
/*   Updated: 2024/07/31 19:06:34 by ecarlier         ###   ########.fr       */
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
		error_message("Error: Invalid object type.\n");
	}
	object->next = NULL;
	free(tmp);
	return (object);
}

void	check_nb_arg(char *save_pointer, int nb)
{
	int			arg_count;
	char		*token;
	char		*temp;
	int			i;

	temp = ft_strdup(save_pointer);
	arg_count = 0;
	i = 0;

	token = ft_strtok_r(NULL, " ", &temp);
	if (token != NULL)
		arg_count++;
	token = ft_strtok_r(NULL, " ", &temp);
	if (token != NULL)
		arg_count++;
	token = ft_strtok_r(NULL, " ", &temp);
	if (token != NULL)
		arg_count++;
	if (nb == 5)
	{
		while (i <= 2)
		{
			token = ft_strtok_r(NULL, " ", &temp);
			if (token != NULL)
				arg_count++;
			i++;
		}
	}

	//free(temp); //segfault


	if (arg_count != nb)
		error_message("Error: Invalid number of arguments of a parameter.\n");
}


t_object	*add_sphere(t_object *object, char *save_pointer)
{
	char		*token;

	check_nb_arg(save_pointer, 3);
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

	check_nb_arg(save_pointer, 3);
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
	token = ft_strtok_r(NULL, " ", &save_pointer);
	object->transformation_matrix = m_translate(object->pos);
	object->inverse_matrix = m_inverse(object->transformation_matrix);
	return (object);
}


t_object	*add_cylinder(t_object *object, char *save_pointer)
{
	char		*token;


	check_nb_arg(save_pointer, 5);
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
