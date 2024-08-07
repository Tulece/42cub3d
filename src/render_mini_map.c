#include "../includes/cub3d.h"
#include "../includes/structs.h"

int	x_off(t_data *data)
{
	int	offset;

	if ((int)floor(data->player.x) + MM_SIZE / 2 > data->map.map_dim.x)
	{
		offset = data->map.map_dim.x - MM_SIZE;
	}
	else if ((int)floor(data->player.x) - MM_SIZE / 2 < 0)
	{
		offset = 0;
	}
	else
	{
		offset = (int)floor(data->player.x) - MM_SIZE / 2;
	}
	return (offset);
}

int	y_off(t_data *data)
{
	int	offset;

	if ((int)floor(data->player.y) + MM_SIZE / 2 > data->map.map_dim.y)
	{
		offset = data->map.map_dim.y - MM_SIZE;
	}
	else if ((int)floor(data->player.y) - MM_SIZE / 2 < 0)
	{
		offset = 0;
	}
	else
	{
		offset = (int)floor(data->player.y) - MM_SIZE / 2;
	}
	return (offset);
}

t_axes	offset_mm(t_data *data, t_axes src)
{
	t_axes	pos;

	pos.x = src.x - x_off(data);
	pos.y = src.y - y_off(data);
	return (pos);
}

void	put_pixel_on_img_offset(t_data *data, t_axes pos, int color, t_img *img)
{
	t_axes	mm_pos;
	t_axes	tile_pos;

	tile_pos.x = pos.x / TILE_SIZE;
	tile_pos.y = pos.y / TILE_SIZE;
	mm_pos = offset_mm(data, tile_pos);
	mm_pos.x *= TILE_SIZE;
	mm_pos.y *= TILE_SIZE;
	mm_pos.x += pos.x % TILE_SIZE;
	mm_pos.y += pos.y % TILE_SIZE;
	put_pixel_on_img(data, mm_pos, color, img);
}

void	render_mini_map(t_data *data, t_img *frame)
{
	t_img	img;

	img.width = MM_SIZE * TILE_SIZE;
	img.heigth = MM_SIZE * TILE_SIZE;
	img.img = mlx_new_image(data->mlx, img.width, img.heigth);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, \
		&img.line_length, &img.endian);
	draw_map(data, &img);
	draw_player(data, &img);
	draw_image_in_image(&img, frame, intopos(0, 0));
	mlx_destroy_image(data->mlx, img.img);
}
