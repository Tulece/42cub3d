/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anporced <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 02:05:09 by anporced          #+#    #+#             */
/*   Updated: 2024/08/08 02:05:10 by anporced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

void	perform_raycasting(t_data *data, t_img *img)
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
