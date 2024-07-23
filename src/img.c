#include "../includes/cub3d.h"

int is_collision(t_data *data, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)(x / TILE_SIZE);
	map_y = (int)(y / TILE_SIZE);
	return (data->map.map[map_y][map_x] == '1');
}

void update_player_position(t_data *data, double delta_x, double delta_y)
{
	double	new_x;
	double	new_y;

	new_x = data->player.x + delta_x;
	new_y = data->player.y + delta_y;
	if (!is_collision(data, new_x, data->player.y))
		data->player.x = new_x;
	if (!is_collision(data, data->player.x, new_y))
		data->player.y = new_y;
}

void	draw_player(t_data *data)
{
	mlx_pixel_put(data->mlx, data->win, (int)data->player.x, (int)data->player.y, 0xFF0000);
}

void	draw_map(t_data *data)
{
	int	x;
	int	y;

	y = -1;
	while (++y < data->map.map_dim.y)
	{
		x = -1;
		while (++x < data->map.map_dim.x)
		{
			if (data->map.map[y][x] == '1')
				mlx_pixel_put(data->mlx, data->win, x * TILE_SIZE, y * TILE_SIZE, 0xFFFFFF); // Dessine les murs en blanc
			else
				mlx_pixel_put(data->mlx, data->win, x * TILE_SIZE, y * TILE_SIZE, 0x000000); // Dessine le sol en noir
		}
	}
}
