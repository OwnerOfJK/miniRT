/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 18:42:22 by ecarlier          #+#    #+#             */
/*   Updated: 2024/05/30 21:06:32 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

/*
/!\ NEED TESTING
*/

double	calc_delta(double a, double b, double c)
{
	double	delta;

	delta = (b * b) - 4 * a * c;
	if (delta < 0)
		return (-1);
	return (delta);
}

/*
/!\ NEED TESTING

updates t1 and t2 with intersections values


a (x*x) + bx + c = 0

if a is 0 and b > 1 -> it's not a quadratic function
bx+c=0.
-> x = -c/b


if delta = 0 -> t1 and t2 should be the same

Return value :
delta or -1 if delta < 0
*/
double	solve_quadratic(t_equat2 *eq)
{
	double	delta;

	delta = calc_delta(eq->a, eq->b, eq->c);
	if (eq->a == 0 && eq->b != 0)
	{
		eq->t1 = - (eq->c) / eq->b;
		return (delta);
	}
	if (delta < 0)
		return (-1);
	if (delta >= 0)
	{
		eq->t1 = (- (eq->b) + sqrt(delta)) / (2 * eq->a);
		eq->t2 = (- (eq->b) - sqrt(delta)) / (2 * eq->a);
	}
	return (delta);
}
