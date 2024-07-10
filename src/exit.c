#include "../includes/cub3d.h"

int	cross_quit(t_data *data)
{
	// free textures + datas
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(0);
}
