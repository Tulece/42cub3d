#include "../includes/cub3d.h"

int handle_keypress(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
		quit(data);
	else if (keycode == KEY_W)
		update_player_position(data, 0, -data->player.speed);
	else if (keycode == KEY_A)
		update_player_position(data, -data->player.speed, 0);
	else if (keycode == KEY_S)
		update_player_position(data, 0, data->player.speed);
	else if (keycode == KEY_D)
		update_player_position(data, data->player.speed, 0);
	return (0);
}

int handle_keyrelease(int keycode, t_data *data)
{
	// Pour l'instant, ne fait rien
	return (0);
}

