#include "../includes/cub3d.h"

// int handle_keypress(int keycode, t_data *data)
// {
// 	if (keycode == KEY_ESC)
// 		quit(data);
// 	else if (keycode == KEY_W)
// 		update_player_position_2(data, 0);
// 	else if (keycode == KEY_A)
// 		update_player_position_2(data, 3);
// 	else if (keycode == KEY_S)
// 		update_player_position_2(data, 1);
// 	else if (keycode == KEY_D)
// 		update_player_position_2(data, 2);
// 	else if (keycode == KEY_R_ARROW)
// 		update_player_dir(data, 1);
// 	else if (keycode == KEY_L_ARROW)
// 		update_player_dir(data, -1);
// 	return (0);
// }

int handle_keypress(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
		quit(data);
	else
	{
		if (keycode == KEY_W)
			data->key_states[KEY_W_I] = 1;
		else if (keycode == KEY_A)
			data->key_states[KEY_A_I] = 1;
		else if (keycode == KEY_S)
			data->key_states[KEY_S_I] = 1;
		else if (keycode == KEY_D)
			data->key_states[KEY_D_I] = 1;
		else if (keycode == KEY_R_ARROW)
			data->key_states[KEY_R_ARROW_I] = 1;
		else if (keycode == KEY_L_ARROW)
			data->key_states[KEY_L_ARROW_I] = 1;
		else if (keycode == KEY_SHIFT)
			data->key_states[KEY_SHIFT_I] = 1;
	}
	return (0);
}

int	handle_keyrelease(int keycode, t_data *data)
{
	if (keycode == KEY_W)
		data->key_states[KEY_W_I] = 0;
	else if (keycode == KEY_A)
		data->key_states[KEY_A_I] = 0;
	else if (keycode == KEY_S)
		data->key_states[KEY_S_I] = 0;
	else if (keycode == KEY_D)
		data->key_states[KEY_D_I] = 0;
	else if (keycode == KEY_R_ARROW)
		data->key_states[KEY_R_ARROW_I] = 0;
	else if (keycode == KEY_L_ARROW)
		data->key_states[KEY_L_ARROW_I] = 0;
	else if (keycode == KEY_SHIFT)
		data->key_states[KEY_SHIFT_I] = 0;
	return (0);
}

