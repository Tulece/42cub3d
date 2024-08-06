#include "../includes/cub3d.h"

void free_map(char **map)
{
	int i;

	if (!map || !*map)
		return;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

int	quit(t_data *data)
{
	if (data->map.map)
	{
		free_map(data->map.map);
	}
	mlx_do_key_autorepeaton(data->mlx);
	free(data->map.map_path);
	free(data->texture.ea_texture.path);
	free(data->texture.no_texture.path);
	free(data->texture.so_texture.path);
	free(data->texture.we_texture.path);
	//Attention si la structure change pour floor et ceiling
	free(data->texture.ceiling_color);
	free(data->texture.floor_color);
	mlx_destroy_image(data->mlx, data->texture.ea_texture.img);
	mlx_destroy_image(data->mlx, data->texture.no_texture.img);
	mlx_destroy_image(data->mlx, data->texture.so_texture.img);
	mlx_destroy_image(data->mlx, data->texture.we_texture.img);
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
