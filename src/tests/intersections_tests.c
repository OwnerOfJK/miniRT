/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections_tests.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaller <jkaller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 20:34:47 by jkaller           #+#    #+#             */
/*   Updated: 2024/06/18 17:48:52 by jkaller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void	test_ray_position(void)
{
	t_ray		*ray;
	t_vector	origin;
	t_vector	direction;
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

void	test_sphere_intersections(t_input	*input)
{
	t_sphere		*sp;
	t_ray			*ray;
	t_intersections	intersections;

	ray = ray_init(v_init(0, 0, -5, 1), v_init(0, 0, 1, 0));
	sp = input->sphere;
	intersections = sphere_intersections(sp, ray);
	assert(intersections.count == 2);
	assert(intersections.t1 == 4);
	assert(intersections.t2 == 6);

	ray = ray_init(v_init(0, 1, -5, 1), v_init(0, 0, 1, 0));
	intersections = sphere_intersections(sp, ray);
	assert(intersections.count == 2);
	assert(intersections.t1 == 5);
	assert(intersections.t2 == 5);

	ray = ray_init(v_init(0, 2, -5, 1), v_init(0, 0, 1, 0));
	intersections = sphere_intersections(sp, ray);
	assert(intersections.count == 0);

	// ray = ray_init(v_init(0, 0, 0, 1), v_init(0, 0, 1, 0));
	// intersections = sphere_intersections(sp, ray);
	// printf("count: %d, t1: %f, t2: %f\n", intersections.count, intersections.t1, intersections.t2);
	// assert(intersections.count == 2);
	// assert(intersections.t1 == -1);
	// assert(intersections.t2 == 1);

	// ray = ray_init(v_init(0, 0, 5, 1), v_init(0, 0, 1, 0));
	// intersections = sphere_intersections(sp, ray);
	// printf("count: %d, t1: %f, t2: %f\n", intersections.count, intersections.t1, intersections.t2);
	// assert(intersections.count == 2);
	// assert(intersections.t1 == -1);
	// assert(intersections.t2 == 1);
}

void	test_ray_transform(void)
{
	t_ray		*ray;
	t_vector	origin;
	t_vector	direction;
	t_vector	position;

	origin = v_init(1, 2, 3, 1);
	direction = v_init(0, 1, 0, 0);
	ray = ray_init(origin, direction);
	position = ray_position(ray, 0);
	assert(position.x == 1);
	assert(position.y == 2);
	assert(position.z == 3);

	*ray = ray_transform(ray, m_translate(v_init(3, 4, 5, 1)));
	position = ray_position(ray, 0);
	assert(position.x == 4);
	assert(position.y == 6);
	assert(position.z == 8);

	*ray = ray_transform(ray, m_scale(v_init(2, 3, 4, 1)));
	position = ray_position(ray, 0);
	assert(position.x == 8);
	assert(position.y == 18);
	assert(position.z == 32);
}

int	test_intersections(t_input	*input)
{
	test_ray_position();
	test_sphere_intersections(input);
	test_ray_transform();

	printf("All intersections tests passed!\n");
	return (0);
}
void test_plane_intersect() {
    t_plane pl;
    t_ray ray;
    t_intersections result;

	pl.pos.x = 0.0;
	pl.pos.y = -5.0;
	pl.pos.z = -10.0;

	pl.normal_vector.x = 0.0;
	pl.normal_vector.y = 1.0;
	pl.normal_vector.z = 0.0;

	pl.color.r = 0;
	pl.color.g = 0;
	pl.color.b = 225;

    // Cas où le rayon doit intersecter le plan (hit)
	ray.origin.x = 0.0;
	ray.origin.y = 0.0;
	ray.origin.z = 0.0;

	ray.direction.x = 0.0;
	ray.direction.y = -1.0; // Direction vers le bas
	ray.direction.z = 0.0;


    printf("Test 1 - Ray hits the plane:\n");
    result = plane_intersect(&pl, &ray);

    if (result.count > 0) {
        printf("Intersection found at t1 = %f\n", result.t1);
        printf("Color of the plane at intersection: (%f, %f, %f)\n", result.color.r, result.color.g, result.color.b);
    } else {
        printf("No intersection found.\n");
    }

    // Cas où le rayon ne doit pas intersecter le plan (miss)
    ray.origin.x = 0.0;
    ray.origin.y = 0.0;
    ray.origin.z = 0.0;

    ray.direction.x = 1.0; // Direction vers la droite, perpendiculaire au plan
    ray.direction.y = 0.0;
    ray.direction.z = 0.0;

    printf("\nTest 2 - Ray misses the plane:\n");
    result = plane_intersect(&pl, &ray);

    if (result.count > 0) {
        printf("Intersection found at t1 = %f\n", result.t1);
        printf("Color of the plane at intersection: (%f, %f, %f)\n", result.color.r, result.color.g, result.color.b);
    } else {
        printf("No intersection found.\n");
    }
}



