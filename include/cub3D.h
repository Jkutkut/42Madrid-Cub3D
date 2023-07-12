/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jre-gonz <jre-gonz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 17:40:06 by jre-gonz          #+#    #+#             */
/*   Updated: 2023/07/11 16:04:50 by jre-gonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D
# define CUB3D

# include <mlx.h>
# include <math.h>
# include <libft.h>
# include <stdio.h> // TODO debug

# define PI 3.14159265

typedef struct s_vector
{
	float	x;
	float	y;
} t_vector;

/*typedef struct s_ray
{
	t_vector	posv;
	t_vector	posh;
	// TODO
} t_ray;*/

typedef struct s_player
{
	t_vector	pos;
	float		angle;
}	t_player;

/**
 * TODO
 * - raycasting must return the distance to a wall.
 * - It will setup a ray to the start of a wall in the direction to check. Both v and h.
 * - It will go until finds any wall, advancing 1 by 1.
 * - Return the min dist. If done at the same time, calculation is instant
 */

// -------------------------
t_vector	vec_new(float x, float y);
void		putvec(const t_vector *v);
float		calc_mag(const t_vector *v);
void		normalize(t_vector *v);

#endif
