/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jre-gonz <jre-gonz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 17:25:16 by jre-gonz          #+#    #+#             */
/*   Updated: 2023/07/10 18:30:31 by jre-gonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

// ------------ Magnitude start ------------

float	calc_mag(const t_vector *v)
{
	return (sqrt(v->x * v->x + v->y * v->y));
}

void	normalize(t_vector *v)
{
	float rsqrt;

	rsqrt = calc_mag(v);
	if (rsqrt != 0.0f) // TODO use epsilon comparison?
		rsqrt = 1 / rsqrt;
	v->x = v->x * rsqrt;
	v->y = v->y * rsqrt;
}

// ------------ Magnitude end ------------


void	putvec(const t_vector *v)
{
	printf("Vec {x: %0.3f, y: %0.3f}\n", v->x, v->y);
}

static t_vector	*fill_vec(t_vector *v, float x, float y)
{
	v->x = x;
	v->y = y;
	return (v);
}

t_vector	vec_new(float x, float y)
{
	t_vector	v;
	return (*fill_vec(&v, x, y));
}