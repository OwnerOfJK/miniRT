/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_utils_0.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 00:23:57 by jkaller           #+#    #+#             */
/*   Updated: 2024/08/05 22:47:03 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

t_object	*ft_lstnew_object(t_data *data, char *str, t_object	*objects_head)
{
	t_object	*object;
	char		*token;
	char		*save_pointer;
	t_context	ctx;

	ctx.tmp = ft_strdup(str);
	ctx.objects_head = objects_head;
	ctx.data = data;
	token = ft_strtok_r(ctx.tmp, " ", &save_pointer);
	object = NULL;
	if (ft_strncmp(token, "sp", 2) == 0)
		object = add_sphere(&ctx, object, save_pointer);
	else if (ft_strncmp(token, "pl", 2) == 0)
		object = add_plane(&ctx, object, save_pointer);
	else if (ft_strncmp(token, "cy", 2) == 0)
		object = add_cylinder(&ctx, object, save_pointer);
	else
		error_free_data(data, "Error: Invalid object type.\n");
	object->next = NULL;
	free(ctx.tmp);
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

bool	check_nb_arg(char *save_pointer, int nb)
{
	int			arg_count;
	char		*token;
	char		*temp;
	int			i;
	char		*to_free;

	temp = ft_strdup(save_pointer);
	arg_count = 0;
	i = 0;
	to_free = temp;
	while (i <= 7)
	{
		token = ft_strtok_r(NULL, " ", &temp);
		if (token != NULL)
			arg_count++;
		i++;
	}
	free(to_free);
	if (arg_count != nb)
		return (true);
	else
		return (false);
}

void	compute_cylinder_m(t_object *object)
{
	t_vector	y_axis;
	t_vector	rotation_axis;
	double		**rotation_matrix;
	double		**translation_matrix;
	double		rotation_angle;

	y_axis = v_init(0, 1, 0, 0);
	rotation_axis = v_cross(y_axis, object->u_shape.s_cylinder.axis_vector);
	rotation_angle = acos(v_dot(y_axis,
				object->u_shape.s_cylinder.axis_vector));
	rotation_matrix = m_rotation(rotation_axis, rotation_angle);
	translation_matrix = m_translate(object->pos);
	object->transformation_matrix = m_mult(translation_matrix, rotation_matrix);
	object->inverse_matrix = m_inverse(object->transformation_matrix);
	free_matrix(rotation_matrix);
	free_matrix(translation_matrix);
}
