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
	ft_bzero(data->key_states, 7 * sizeof(int));
	data->player.dir_x = -1;
	data->player.dir_y = 0;
	data->player.plane_x = 0;
	data->player.plane_y = 0;
	data->player.speed = 0.1;
	data->player.pov_speed = 3.0;
	data->map.map = NULL;
	data->texture.no_texture.path = NULL;
	data->texture.so_texture.path = NULL;
	data->texture.ea_texture.path = NULL;
	data->texture.we_texture.path = NULL;
	data->texture.ceiling_color = NULL;
	data->texture.floor_color = NULL;
}

void	init_single_texture(t_data *data, t_img *texture)
{
	int	width;
	int	height;

	texture->img = mlx_xpm_file_to_image(data->mlx, texture->path, \
	&width, &height);
	texture->addr = mlx_get_data_addr(texture->img, &texture->bpp, \
	&texture->line_length, &texture->endian);
	texture->width = width;
	texture->heigth = height;
}

void	init_no_texture(t_data *data)
{
	init_single_texture(data, &data->texture.no_texture);
}

void	init_so_texture(t_data *data)
{
	init_single_texture(data, &data->texture.so_texture);
}

void	init_we_texture(t_data *data)
{
	init_single_texture(data, &data->texture.we_texture);
}

void	init_ea_texture(t_data *data)
{
	init_single_texture(data, &data->texture.ea_texture);
}

void	init_textures(t_data *data)
{
	init_no_texture(data);
	init_so_texture(data);
	init_we_texture(data);
	init_ea_texture(data);
}
