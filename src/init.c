#include "../includes/cub3d.h"

void init_data(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		error_exit("Failed to initialize MLX", data);
	data->win = mlx_new_window(data->mlx, 800, 600, "Cub3D");
	if (!data->win)
		error_exit("Failed to create window", data);
	data->player.x = 1.5 * TILE_SIZE; // Par exemple, initialiser au centre d'une case
	data->player.y = 1.5 * TILE_SIZE; // Par exemple, initialiser au centre d'une case
	data->player.dir_x = -1;
	data->player.dir_y = 0;
	data->player.plane_x = 0;
	data->player.plane_y = 0.66;
	data->player.speed = 2.0; // Vitesse du joueur en pixels
}

// void init_textures(t_data *data)
// {
// 	int width, height;
// 	//verif pour initialisation des textures
// 	data->textures[0].img = mlx_xpm_file_to_image(data->mlx, "path_to_north_texture.xpm", &width, &height);
// 	data->textures[1].img = mlx_xpm_file_to_image(data->mlx, "path_to_south_texture.xpm", &width, &height);
// 	data->textures[2].img = mlx_xpm_file_to_image(data->mlx, "path_to_west_texture.xpm", &width, &height);
// 	data->textures[3].img = mlx_xpm_file_to_image(data->mlx, "path_to_east_texture.xpm", &width, &height);
// }

// void init_colors(t_data *data)
// {
// 	data->floor_color = 0x00FF00;
// 	data->ceiling_color = 0x0000FF;
// }
