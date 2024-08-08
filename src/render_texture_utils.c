/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_texture_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anporced <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 02:05:05 by anporced          #+#    #+#             */
/*   Updated: 2024/08/08 02:05:06 by anporced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
