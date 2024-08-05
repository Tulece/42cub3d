#include "../includes/cub3d.h"

void	calculate_vectors(t_player *player)
{
	double	rad_angle;

	rad_angle = degrad(player->deg_dir);
	player->dir_x = cos(rad_angle);
	player->dir_y = sin(rad_angle);
	player->plane_x = -player->dir_y * 0.66;
	player->plane_y = player->dir_x * 0.66;
}


void	init_data(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		error_exit("Failed to initialize MLX", data);
	data->win = mlx_new_window(data->mlx, 800, 600, "Cub3D");
	if (!data->win)
		error_exit("Failed to create window", data);
	ft_bzero(data->key_states, 6 * sizeof(int));
	data->player.dir_x = -1;
	data->player.dir_y = 0;
	data->player.plane_x = 0;
	data->player.plane_y = 0;
	data->player.speed = 0.2;
	data->player.pov_speed = 2.0;
}

void	init_textures(t_data *data)
{
	int	width;
	int	height;

	data->texture.no_texture.img = mlx_xpm_file_to_image(data->mlx, data->texture.no_texture.path, &width, &height);
	data->texture.no_texture.addr = mlx_get_data_addr(data->texture.no_texture.img, &data->texture.no_texture.bpp, &data->texture.no_texture.line_length, &data->texture.no_texture.endian);
	data->texture.no_texture.width = width;
	data->texture.no_texture.heigth = height;
	data->texture.so_texture.img = mlx_xpm_file_to_image(data->mlx, data->texture.so_texture.path, &width, &height);
	data->texture.so_texture.addr = mlx_get_data_addr(data->texture.so_texture.img, &data->texture.so_texture.bpp, &data->texture.so_texture.line_length, &data->texture.so_texture.endian);
	data->texture.so_texture.width = width;
	data->texture.so_texture.heigth = height;
	data->texture.we_texture.img = mlx_xpm_file_to_image(data->mlx, data->texture.we_texture.path, &width, &height);
	data->texture.we_texture.addr = mlx_get_data_addr(data->texture.we_texture.img, &data->texture.we_texture.bpp, &data->texture.we_texture.line_length, &data->texture.we_texture.endian);
	data->texture.we_texture.width = width;
	data->texture.we_texture.heigth = height;
	data->texture.ea_texture.img = mlx_xpm_file_to_image(data->mlx, data->texture.ea_texture.path, &width, &height);
	data->texture.ea_texture.addr = mlx_get_data_addr(data->texture.ea_texture.img, &data->texture.ea_texture.bpp, &data->texture.ea_texture.line_length, &data->texture.ea_texture.endian);
	data->texture.ea_texture.width = width;
	data->texture.ea_texture.heigth = height;
}
