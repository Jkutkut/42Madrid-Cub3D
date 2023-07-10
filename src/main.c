/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jre-gonz <jre-gonz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 17:59:17 by jre-gonz          #+#    #+#             */
/*   Updated: 2023/07/10 23:15:02 by jre-gonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>

int	ft_abs(int nbr)
{
	if (nbr < 0)
		return -nbr;
	return nbr;
}

// ----------------------------------------

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	basic_test(t_data img)
{
	int color = 0x01000000;
	for (int i = 0, j; i < 1920; i++) {
		for (j = 0; j < 1080; j++) {
			my_mlx_pixel_put(&img, i, j, color);
			color = color + 0x00001;
		}
	}
}


// ----------------------------------------


# define RESOLUTION_X 1920
# define RESOLUTION_Y 1080

# define FOV 1.570796327 // PI/2 rad: Angle of vision of the player
# define DTHETA 0.1570796 // PI/20 -> 10 rays per rad. TODO analyze

void	bg(t_data *img)
{
	int y, x;

	for (y = 0; y < RESOLUTION_Y / 2; y++)
	{
		for (x = 0; x < RESOLUTION_X; x++)
		{
			my_mlx_pixel_put(img, x, y, 0xdbdbdb);
		}
	}
	for (; y < RESOLUTION_Y; y++)
	{
		for (x = 0; x < RESOLUTION_X; x++)
		{
			my_mlx_pixel_put(img, x, y, 0x878787);
		}
	}
}

/*void	draw_wall(t_data img, int x, int size)
{
	for (int i = -size / 2; i < size / 2; i++)
	{
		my_mlx_pixel_put(&img, x, 1080 / 2 + i, 0xff0000);
	}
}*/

void	draw(t_data *img, char **map, t_player *player)
{
	(void) map;

	bg(img);
	// --------------------
	player->angle = player->angle % (2 * PI);
	float theta = - (FOV << 1);
	while (theta < FOV << 1)
	{
		float dist = raycast(map, player, theta);

		//draw_wall(img, angle, dist);

		theta += DTHETA;
	}
	// --------------------
	for (int angle = -(FOV << 1); angle < FOV << 1; angle++)
	{
	}
	// -------------------
}


int	main(void)
{
	void		*mlx;
	void		*mlx_win;
	t_data		img;
	t_player	player;

	char	map[10][10] = {
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 1, 1, 0, 1, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
	};

	player.pos = vec_new(5, 5);
	player.angle = PI / 2;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	// basic_test(img);
	draw(&img, (char **) map, &player);
	
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}
