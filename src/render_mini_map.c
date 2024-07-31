#include "../includes/cub3d.h"
#include "../includes/structs.h"

void	put_pixel_on_img(t_data *data, t_axes pos, int color, t_img *img)
{
	int pixel;

	pixel = (pos.x * 4) + (pos.y * img->line_length);
    img->addr[pixel] = color & 0xFF; // Blue
    img->addr[pixel + 1] = (color >> 8) & 0xFF; // Green
    img->addr[pixel + 2] = (color >> 16) & 0xFF; // Red
    img->addr[pixel + 3] = (color >> 24) & 0xFF;
}

void draw_tile(t_data *data, t_axes pos, int color, t_img *img)
{
	t_axes new_pos;
	t_axes pix_pos;

	new_pos.x = pos.x * TILE_SIZE;
	new_pos.y = pos.y * TILE_SIZE;
	for (int i = 0; i < TILE_SIZE; i++)
	{
		for (int j = 0; j < TILE_SIZE; j++)
		{
			pix_pos.x = new_pos.x + j;
			pix_pos.y = new_pos.y + i;
			put_pixel_on_img(data, pix_pos, color, img);
		}
	}
}

void draw_map(t_data *data, t_img *img)
{
	t_axes pos;

	pos.y = 0;
	for (pos.y = 0; pos.y < data->map.map_dim.y; pos.y++)
	{
		for (pos.x = 0; pos.x < data->map.map_dim.x; pos.x++)
		{
			if (data->map.map[pos.y][pos.x] == '1')
				draw_tile(data, pos, 0xFFFFFF, img);
			else
				draw_tile(data, pos, 0x000000, img);
		}
	}
}


void draw_view(t_data *data, t_img *img)
{
	int		i;
	double	j;
	double	angle;
	t_axes	pos;

	i = 0;
	while (i < 90)
	{
		j = 0;
		angle = degrad(data->player.deg_dir - 44 + 90 + (i * (44.0 / 45))); // Ajustement de l'angle
		while (j < 40)
		{
			pos.x = (int)(data->player.x * TILE_SIZE + j * sin(angle));
			pos.y = (int)(data->player.y * TILE_SIZE + j * cos(angle));
			if (!is_collision(data, pos.x / TILE_SIZE, pos.y / TILE_SIZE))
			{
				put_pixel_on_img(data, pos, 0xFF0000, img);
			}
			else
				break;
			j += 0.1;
		}
		i++;
	}
}


void draw_player(t_data *data, t_img *img)
{
	int		i;
	int		j;
	t_axes	pos;

	i = 0;
	pos.x = (int)(data->player.x * TILE_SIZE - 2);
	pos.y = ((int)(data->player.y * TILE_SIZE) - 2);
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			put_pixel_on_img(data, pos, 0xFF0000, img);
			j++;
			pos.x++;
		}
		i++;
		pos.y++;
	}
	draw_view(data, img);
}

void    render_mini_map(t_data *data)
{
	t_img	img;
	int		width;
	int		heigth;

	width = data->map.map_dim.x * TILE_SIZE;
	heigth = data->map.map_dim.y * TILE_SIZE;
	img.img = mlx_new_image(data->mlx, width, heigth);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_length, &img.endian);
	draw_map(data, &img);
	draw_player(data, &img);
	mlx_put_image_to_window(data->mlx, data->win, img.img, 0, 0);
}
