#include "../includes/cub3d.h"

int	is_view_collision(t_data *data, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)(x);
	map_y = (int)(y);
	if (map_x < 0 || map_x >= data->map.map_dim.x || map_y < 0 \
	|| map_y >= data->map.map_dim.y)
		return (1);
	if (data->map.map[map_y][map_x] == '1' \
	|| data->map.map[map_y][map_x] == ' ')
		return (1);
	return (0);
}

void	set_pos(t_axes *pos, int x, int y)
{
	pos->x = x;
	pos->y = y;
}

int	is_collision(t_data *data, double x, double y)
{
	int		map_x;
	int		map_y;
	int		i;
	double	margin;
	t_axes	points_to_check[4];

	margin = 0.2;
	set_pos(&points_to_check[0], x - margin, y - margin);
	set_pos(&points_to_check[1], x + margin, y - margin);
	set_pos(&points_to_check[2], x - margin, y + margin);
	set_pos(&points_to_check[3], x + margin, y + margin);
	i = 0;
	while (i < 4)
	{
		map_x = (int)(points_to_check[i].x);
		map_y = (int)(points_to_check[i].y);
		if (map_x < 0 || map_x >= data->map.map_dim.x || map_y < 0 || \
		map_y >= data->map.map_dim.y)
			return (1);
		if (data->map.map[map_y][map_x] == '1' || \
		data->map.map[map_y][map_x] == ' ')
			return (1);
		i++;
	}
	return (0);
}

void	update_player_dir(t_data *data, int dir)
{
	data->player.deg_dir += data->player.pov_speed * dir;
	if (data->player.deg_dir >= 360)
		data->player.deg_dir -= 360;
	else if (data->player.deg_dir < 0)
		data->player.deg_dir += 360;
	calculate_vectors(&data->player);
}

void	update_player_position(t_data *data, double delta_x, double delta_y)
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
