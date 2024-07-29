#include "../includes/cub3d.h"

int render_frame(t_data *data)
{
	// mlx_clear_window(data->mlx, data->win);
	draw_map(data);
	draw_player(data);
	return (0);
}


