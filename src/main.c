/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jre-gonz <jre-gonz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 17:59:17 by jre-gonz          #+#    #+#             */
/*   Updated: 2023/07/06 17:41:09 by jre-gonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# define FOCAL_LENGTH 0.8

void	bg(t_data img)
{
	int y, x;

	for (y = 0; y < RESOLUTION_Y / 2; y++)
	{
		for (x = 0; x < RESOLUTION_X; x++)
		{
			my_mlx_pixel_put(&img, x, y, 0xdbdbdb);
		}
	}
	for (; y < RESOLUTION_Y; y++)
	{
		for (x = 0; x < RESOLUTION_X; x++)
		{
			my_mlx_pixel_put(&img, x, y, 0x878787);
		}
	}
}

void	ray_tracing(t_data img, char **map)
{
	(void) img;
	(void) map;
	// float	px = 5.0;
	// float	py = 5.0;

	bg(img);

	/*for (int col = 0, j; col < RESOLUTION_X; col++) {
		float x = col / RESOLUTION_X - 0.5; // range from -0.5 to 0.5
		float angle = atan2(x, FOCAL_LENGTH);
		//var ray = map.cast(player, player.direction + angle, this.range);
		drawColumn(col, ray, angle, map);
	}*/
}

// void	drawColumn(int col, void ray, float angle, char **map)
// {

// }


int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;

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

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	// basic_test(img);
	ray_tracing(img,(char **) map);
	
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}
