/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anporced <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 02:04:20 by anporced          #+#    #+#             */
/*   Updated: 2024/08/08 02:04:22 by anporced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	initialize_ray(t_data *data, t_ray *ray, int x)
{
	ray->camera_x = 2 * x / 800.0 - 1;
	ray->ray_dir_x = data->player.dir_x + data->player.plane_x * ray->camera_x;
	ray->ray_dir_y = data->player.dir_y + data->player.plane_y * ray->camera_x;
	ray->map_x = (int)data->player.x;
	ray->map_y = (int)data->player.y;
	ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	ray->hit = 0;
}

void	initialize_map(t_data *data, char **lines, int map_start_index)
{
	data->map.map = dup_tab(&lines[map_start_index]);
	ft_free_tab(lines);
	data->map.map_dim = map_size(data);
}
