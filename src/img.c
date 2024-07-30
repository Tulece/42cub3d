#include "../includes/cub3d.h"

int is_collision(t_data *data, double x, double y)
{
	int map_x;
	int map_y;

	map_x = (int)(x);
	map_y = (int)(y);

	if (map_x < 0 || map_x >= data->map.map_dim.x || map_y < 0 || map_y >= data->map.map_dim.y)
		return 1; // Treat out-of-bounds as a collision
	if (data->map.map[map_y][map_x] == '1' || data->map.map[map_y][map_x] == ' ')
		return 1;
	return (0);
}

void update_player_dir(t_data *data, int dir)
{
	data->player.deg_dir += data->player.pov_speed * dir;
	if (data->player.deg_dir >= 360)
		data->player.deg_dir -= 360;
	else if (data->player.deg_dir < 0)
		data->player.deg_dir += 360;
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

void update_player_position_2(t_data *data, int dir)
{
	double	d_x;
	double	d_y;
	double	d_dir;

	d_dir = dir * 90;
	d_dir += data->player.deg_dir;
	if (d_dir > 360)
		d_dir -= 360;
	d_x = data->player.speed * sin(degrad(d_dir));
	d_y = data->player.speed * cos(degrad(d_dir));
	update_player_position(data, d_x, d_y);
}

void draw_tile(t_data *data, int x, int y, int color)
{
	int pixel_x = x * TILE_SIZE;
	int pixel_y = y * TILE_SIZE;
	for (int i = 0; i < TILE_SIZE; i++)
	{
		for (int j = 0; j < TILE_SIZE; j++)
		{
			mlx_pixel_put(data->mlx, data->win, pixel_x + j, pixel_y + i, color);
		}

	}

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
				draw_tile(data, x, y, 0xFFFFFF);
			else
				draw_tile(data, x, y, 0x000000);
		}
	}
}

double	degrad(double deg)
{
	return (((deg)) * (PI / 180.0));
}

void draw_view(t_data *data)
{
    int		i;
    double	j;
    double	angle;
	t_axes	pos;

    i = 0;
    while (i < 90)
    {
        j = 0;
        angle = degrad(data->player.deg_dir - 44 + 90 + (i * (44.0 / 45))); // Ajustement de l'angle
        while (j < 40)
        {
            pos.x = (int)(data->player.x * TILE_SIZE + j * sin(angle));
            pos.y = (int)(data->player.y * TILE_SIZE + j * cos(angle));
			if (!is_collision(data, pos.x / TILE_SIZE, pos.y / TILE_SIZE))
			{
	            mlx_pixel_put(data->mlx, data->win, pos.x, pos.y, 0xFF0000);
			}
			else
				break;
            j += 0.1;
        }
        i++;
    }
}


void draw_player(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			mlx_pixel_put(data->mlx, data->win, ((int)(data->player.x * TILE_SIZE - 2)) + j, ((int)(data->player.y * TILE_SIZE) - 2) + i, 0xFF0000);
			j++;
		}
		i++;
	}
	draw_view(data);
}
