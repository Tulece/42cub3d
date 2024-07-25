#include "../includes/cub3d.h"

int is_collision(t_data *data, double x, double y)
{
	int map_x;
	int map_y;

	map_x = (int)(x / TILE_SIZE);
	map_y = (int)(y / TILE_SIZE);

	if (map_x < 0 || map_x >= data->map.map_dim.x || map_y < 0 || map_y >= data->map.map_dim.y)
		return 1; // Treat out-of-bounds as a collision
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

void draw_tile(t_data *data, int x, int y, int color)
{
	int pixel_x = x * TILE_SIZE;
	int pixel_y = y * TILE_SIZE;
	mlx_pixel_put(data->mlx, data->win, pixel_x, pixel_y, color);
}

void draw_map(t_data *data)
{
	int x;
	int y;

	for (y = 0; y < data->map.map_dim.y; y++)
	{
		for (x = 0; x < data->map.map_dim.x; x++)
		{
			if (data->map.map[y][x] == '1')
				draw_tile(data, x, y, 0xFFFFFF); // Blanc pour les murs
			else
				draw_tile(data, x, y, 0x000000); // Noir pour le sol
		}
	}
}

void draw_player(t_data *data)
{
	int player_pixel_x = (int)(data->player.x);
	int player_pixel_y = (int)(data->player.y);
	mlx_pixel_put(data->mlx, data->win, player_pixel_x, player_pixel_y, 0xFF0000); // Rouge pour le joueur
}
