#include "../includes/cub3d.h"

int is_view_collision(t_data *data, double x, double y)
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

#include <math.h>

int is_collision(t_data *data, double x, double y)
{
    int map_x;
    int map_y;
	int	i;
    double margin = 0.2;
    double points_to_check[4][2] = {
        {x - margin, y - margin},
        {x + margin, y - margin},
        {x - margin, y + margin},
        {x + margin, y + margin}
    };

	i = 0;
    while (i < 4)
    {
        map_x = (int)(points_to_check[i][0]);
        map_y = (int)(points_to_check[i][1]);
        if (map_x < 0 || map_x >= data->map.map_dim.x || map_y < 0 || map_y >= data->map.map_dim.y)
            return 1; // Considérer hors limites comme une collision
        if (data->map.map[map_y][map_x] == '1' || data->map.map[map_y][map_x] == ' ')
            return 1;
		i++;
    }
    return 0;
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

void update_player_position_2(t_data *data, int dir, int run)
{
	double d_x = 0.0;
	double d_y = 0.0;

	if (dir == 0) {
		// Déplacement vers l'avant
		d_x = (data->player.speed * (1 + run)) * cos(degrad(data->player.deg_dir));
		d_y = (data->player.speed * (1 + run)) * sin(degrad(data->player.deg_dir));
	} else if (dir == 1) {
		// Déplacement vers l'arrière
		d_x = (-data->player.speed * (1 + run)) * cos(degrad(data->player.deg_dir));
		d_y = (-data->player.speed * (1 + run)) * sin(degrad(data->player.deg_dir));
	} else if (dir == 2) {
		// Déplacement vers la gauche
		d_x = (-data->player.speed * (1 + run)) * sin(degrad(data->player.deg_dir));
		d_y = (data->player.speed * (1 + run)) * cos(degrad(data->player.deg_dir));
	} else if (dir == 3) {
		// Déplacement vers la droite
		d_x = (data->player.speed * (1 + run)) * sin(degrad(data->player.deg_dir));
		d_y = (-data->player.speed * (1 + run)) * cos(degrad(data->player.deg_dir));
	}

	update_player_position(data, d_x, d_y);
}

double	degrad(double deg)
{
	return (((deg)) * (PI / 180.0));
}
