/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jre-gonz <jre-gonz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 17:40:06 by jre-gonz          #+#    #+#             */
/*   Updated: 2023/07/10 18:03:26 by jre-gonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D
# define CUB3D

# include <mlx.h>
# include <math.h>
# include <libft.h>
# include <stdio.h> // TODO debug

typedef struct s_vector
{
	float	x;
	float	y;
} t_vector;

// -------------------------
t_vector	vec_new(float x, float y);
void		putvec(const t_vector *v);
float		calc_mag(const t_vector *v);
void		normalize(t_vector *v);

#endif