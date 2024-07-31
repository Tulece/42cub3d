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
	calculate_vectors(&data->player);
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

double	degrad(double deg)
{
	return (((deg)) * (PI / 180.0));
}
