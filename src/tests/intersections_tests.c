/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections_tests.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 20:34:47 by jkaller           #+#    #+#             */
/*   Updated: 2024/06/13 21:12:11 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void test_ray_position(void)
{
    t_ray       *ray;
    t_vector    origin;
    t_vector    direction;
    t_vector	position;

    origin = v_init(2, 3, 4, 1);
    direction = v_init(1, 0, 0, 0);
    ray = ray_init(origin, direction);
    position = ray_position(ray, 0);
    assert(position.x == 2);
    assert(position.y == 3);
    assert(position.z == 4);

    position = ray_position(ray, 1);
    assert(position.x == 3);
    assert(position.y == 3);
    assert(position.z == 4);

    position = ray_position(ray, -1);
    assert(position.x == 1);
    assert(position.y == 3);
    assert(position.z == 4);

    position = ray_position(ray, 2.5);
    assert(position.x == 4.5);
    assert(position.y == 3);
    assert(position.z == 4);
}

int test_intersections(void)
{
	test_ray_position();

	printf("All intersections tests passed!\n");
	return (0);
}