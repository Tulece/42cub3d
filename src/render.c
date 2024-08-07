#include "../includes/cub3d.h"

t_axes	intopos(int x, int y)
{
	t_axes	pos;

	pos.x = x;
	pos.y = y;
	return (pos);
}

int	get_texture_color(t_img *texture, int x, int y)
{
	char	*pixel;

	if (x < 0)
		x = 0;
	if (x >= texture->width)
		x = texture->width - 1;
	if (y < 0)
		y = 0;
	if (y >= texture->heigth)
		y = texture->heigth - 1;
	pixel = texture->addr + (y * texture->line_length + x * (texture->bpp / 8));
	return (*(int *)pixel);
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

void	calculate_step_and_initial_side_dist(t_data *data, t_ray *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (data->player.x - ray->map_x) \
		* ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - data->player.x) \
		* ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (data->player.y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - data->player.y) \
		* ray->delta_dist_y;
	}
}

void	perform_dda(t_data *data, t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (data->map.map[ray->map_y][ray->map_x] > '0')
			ray->hit = 1;
	}
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - data->player.x + \
		(1 - ray->step_x) / 2) / ray->ray_dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - data->player.y + \
		(1 - ray->step_y) / 2) / ray->ray_dir_y;
}


void calculate_line_height_and_draw_positions(t_ray *ray, int screen_height)
{
	ray->line_height = (int)(screen_height / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + screen_height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + screen_height / 2;
	if (ray->draw_end >= screen_height)
		ray->draw_end = screen_height - 1;
}

void	select_texture(t_data *data, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			ray->texture = &data->texture.we_texture;
		else
			ray->texture = &data->texture.ea_texture;

	}
	else
	{
		if (ray->ray_dir_y > 0)
			ray->texture = &data->texture.no_texture;
		else
			ray->texture = &data->texture.so_texture;
	}
}

void	calculate_wall_and_texture_x(t_data *data, t_ray *ray)
{
	if (ray->side == 0)
		ray->wall_x = data->player.y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		ray->wall_x = data->player.x + ray->perp_wall_dist * ray->ray_dir_x;
	ray->wall_x -= floor(ray->wall_x);
	ray->tex_x = (int)(ray->wall_x * (double)ray->texture->width);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		ray->tex_x = ray->texture->width - ray->tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		ray->tex_x = ray->texture->width - ray->tex_x - 1;
}

void	calculate_line_and_texture(t_data *data, t_ray *ray)
{
	int	screen_height;

	screen_height = 600;
	calculate_line_height_and_draw_positions(ray, screen_height);
	select_texture(data, ray);
	calculate_wall_and_texture_x(data, ray);
}


void	draw_vertical_stripe(t_data *data, t_ray *ray, t_img *img, int x)
{
	int	y;
	int	d;

	y = ray->draw_start - 1;
	while (++y < ray->draw_end)
	{
		d = y * 256 - 600 * 128 + ray->line_height * 128;
		ray->tex_y = ((d * ray->texture->heigth) / ray->line_height) / 256;
		ray->color = get_texture_color(ray->texture, ray->tex_x, ray->tex_y);
		put_pixel_on_img(data, intopos(x, y), ray->color, img);
	}
	y = -1;
	while (++y < ray->draw_start)
		put_pixel_on_img(data, intopos(x, y), data->texture.ceiling, img);
	y = ray->draw_end - 1;
	while (++y < 600)
		put_pixel_on_img(data, intopos(x, y), data->texture.floor, img);
}

void perform_raycasting(t_data *data, t_img *img)
{
	t_ray	ray;
	int		x;

	x = -1;
	while (++x < 800)
	{
		initialize_ray(data, &ray, x);
		calculate_step_and_initial_side_dist(data, &ray);
		perform_dda(data, &ray);
		calculate_line_and_texture(data, &ray);
		draw_vertical_stripe(data, &ray, img, x);
	}
}

void	calculate_infos(t_data *data)
{
	if (data->key_states[KEY_W_I])
		update_player_position_2(data, 0, data->key_states[KEY_SHIFT_I]);
	if (data->key_states[KEY_A_I])
		update_player_position_2(data, 3, data->key_states[KEY_SHIFT_I]);
	if (data->key_states[KEY_S_I])
		update_player_position_2(data, 1, data->key_states[KEY_SHIFT_I]);
	if (data->key_states[KEY_D_I])
		update_player_position_2(data, 2, data->key_states[KEY_SHIFT_I]);
	if (data->key_states[KEY_R_ARROW_I])
		update_player_dir(data, 1);
	if (data->key_states[KEY_L_ARROW_I])
		update_player_dir(data, -1);
}

int	render_frame(t_data *data)
{
	t_img	img;

	img.width = 800;
	img.heigth = 600;
	img.img = mlx_new_image(data->mlx, img.width, img.heigth);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, \
	&img.line_length, &img.endian);
	calculate_infos(data);
	perform_raycasting(data, &img);
	render_mini_map(data, &img);
	mlx_put_image_to_window(data->mlx, data->win, img.img, 0, 0);
	mlx_destroy_image(data->mlx, img.img);
	return (0);
}


