#include "../includes/cub3d.h"

void free_map(char **map)
{
	int i;

	if (!map)
		return;
	i = -1;
	while (map[++i])
		free(map[i]);
	free(map);
}

int	quit(t_data *data)
{
	// if (data->map.map)
		// free_map(data->map.map);
	if (data->mlx && data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
		mlx_destroy_display(data->mlx);
	if (data->mlx)
		free(data->mlx);
	exit(0);
}

int	cross_quit(t_data *data)
{
	return (quit(data));
}
