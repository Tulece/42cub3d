/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map_draw.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgibert <tgibert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 02:04:01 by tgibert           #+#    #+#             */
/*   Updated: 2024/08/08 02:04:07 by tgibert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../includes/structs.h"

void	draw_tile(t_data *data, t_axes pos, int color, t_img *img)
{
	t_axes	pix_pos;
	int		i;
	int		j;

	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			pix_pos.x = (pos.x * TILE_SIZE) + j;
			pix_pos.y = (pos.y * TILE_SIZE) + i;
			put_pixel_on_img(data, pix_pos, color, img);
			j++;
		}
		i++;
	}
}

void	draw_map(t_data *data, t_img *img)
{
	t_axes	pos;
	t_axes	p_pos;

	pos.y = -1;
	while (++pos.y < MM_SIZE)
	{
		pos.x = -1;
		while (++pos.x < MM_SIZE)
		{
			p_pos.x = x_off(data) + pos.x;
			p_pos.y = y_off(data) + pos.y;
			if (p_pos.x >= 0 && p_pos.x < data->map.map_dim.x && \
				p_pos.y >= 0 && p_pos.y < data->map.map_dim.y)
			{
				if (data->map.map[p_pos.y][p_pos.x] == '1')
					draw_tile(data, pos, 0xFFFFFF, img);
				else if (data->map.map[p_pos.y][p_pos.x] == '0')
					draw_tile(data, pos, 0x888888, img);
				else
					draw_tile(data, pos, 0x000000, img);
			}
			else
				draw_tile(data, pos, 0x555555, img);
		}
	}
}

void	draw_view(t_data *data, t_img *img)
{
	int		i;
	double	j;
	double	angle;
	t_axes	pos;

	i = 0;
	while (i < 70)
	{
		j = 0;
		angle = degrad(data->player.deg_dir - 34 + (i * (44.0 / 45)));
		while (j < 35)
		{
			pos.x = (int)(data->player.x * TILE_SIZE + j * cos(angle));
			pos.y = (int)(data->player.y * TILE_SIZE + j * sin(angle));
			if (!is_view_collision(data, pos.x / TILE_SIZE, pos.y / TILE_SIZE))
			{
				put_pixel_on_img_offset(data, pos, 0xFF0000, img);
			}
			else
				break ;
			j += 0.1;
		}
		i++;
	}
}

void	draw_player(t_data *data, t_img *img)
{
	int		i;
	int		j;
	t_axes	s_pos;
	t_axes	pos;

	i = 0;
	s_pos.x = ((int)(data->player.x * TILE_SIZE) - 2);
	s_pos.y = ((int)(data->player.y * TILE_SIZE) - 2);
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			pos.x = s_pos.x + j;
			pos.y = s_pos.y + i;
			put_pixel_on_img_offset(data, pos, 0xFF0000, img);
			j++;
		}
		i++;
	}
	draw_view(data, img);
}

void	draw_image_in_image(t_img *src, t_img *dst, t_axes pos)
{
	int	x;
	int	y;
	int	pixel_src;
	int	pixel_dst;

	y = 0;
	while (y < src->heigth)
	{
		x = 0;
		while (x < src->width)
		{
			pixel_src = y * src->line_length + x * (src->bpp / 8);
			pixel_dst = (pos.y + y) * dst->line_length + \
				(pos.x + x) * (dst->bpp / 8);
			dst->addr[pixel_dst] = src->addr[pixel_src];
			dst->addr[pixel_dst + 1] = src->addr[pixel_src + 1];
			dst->addr[pixel_dst + 2] = src->addr[pixel_src + 2];
			dst->addr[pixel_dst + 3] = src->addr[pixel_src + 3];
			x++;
		}
		y++;
	}
}
