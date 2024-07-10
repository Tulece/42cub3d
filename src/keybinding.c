#include "../includes/cub3d.h"

int	hook_switch(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
		quit(data);
	return (0);
}