#include "../includes/cub3d.h"

t_axes intopos(int x, int y)
{
	t_axes pos;

	pos.x = x;
	pos.y = y;
	return (pos);
}

int get_texture_color(t_img *texture, int x, int y) {
	if (x < 0) x = 0;
	if (x >= texture->width) x = texture->width - 1;
	if (y < 0) y = 0;
	if (y >= texture->heigth) y = texture->heigth - 1;

	char *pixel = texture->addr + (y * texture->line_length + x * (texture->bpp / 8));
	return *(int *)pixel;
}

void	perform_raycasting(t_data *data, t_img *img)
{
	int		x;
	double	cameraX;
	double	rayDirX;
	double	rayDirY;
	int		mapX;
	int		mapY;
	double	sideDistX;
	double	sideDistY;
	double	deltaDistX;
	double	deltaDistY;
	double	perpWallDist;
	int		stepX;
	int		stepY;
	int		hit;
	int		side;
	int		lineHeight;
	int		drawStart;
	int		drawEnd;
	t_img	*texture;
	double	wallX;

	x = -1;
	while (++x < 800)
	{
		cameraX = 2 * x / 800.0 - 1;
		rayDirX = data->player.dir_x + data->player.plane_x * cameraX;
		rayDirY = data->player.dir_y + data->player.plane_y * cameraX;

		mapX = (int)data->player.x;
		mapY = (int)data->player.y;

		deltaDistX = fabs(1 / rayDirX);
		deltaDistY = fabs(1 / rayDirY);


		hit = 0;

		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (data->player.x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - data->player.x) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (data->player.y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - data->player.y) * deltaDistY;
		}

		while (hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (data->map.map[mapY][mapX] > '0')
				hit = 1;
		}
		if (side == 0)
			perpWallDist = (mapX - data->player.x + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - data->player.y + (1 - stepY) / 2) / rayDirY;

		lineHeight = (int)(600 / perpWallDist);

		drawStart = -lineHeight / 2 + 600 / 2;
		if (drawStart < 0)
			drawStart = 0;
		drawEnd = lineHeight / 2 + 600 / 2;
		if (drawEnd >= 600)
			drawEnd = 600 - 1;
		// Select the correct texture
		if (side == 0)
		{
			texture = (rayDirX > 0) ? &data->texture.we_texture : &data->texture.ea_texture;
		}
		else
			texture = (rayDirY > 0) ? &data->texture.no_texture : &data->texture.so_texture;

		if (side == 0)
			wallX = data->player.y + perpWallDist * rayDirY;
		else
			wallX = data->player.x + perpWallDist * rayDirX;
		wallX -= floor(wallX);

		int texX = (int)(wallX * (double)texture->width);
		if (side == 0 && rayDirX > 0) texX = texture->width - texX - 1;
		if (side == 1 && rayDirY < 0) texX = texture->width - texX - 1;

		for (int y = drawStart; y < drawEnd; y++)
		{
			int d = y * 256 - 600 * 128 + lineHeight * 128;
			int texY = ((d * texture->heigth) / lineHeight) / 256;
			int color = get_texture_color(texture, texX, texY);
			put_pixel_on_img(data, intopos(x, y), color, img);
		}
		// Draw ceiling
		for (int y = 0; y < drawStart; y++)
		{
			put_pixel_on_img(data, intopos(x, y), 0x000000, img);
		}

		// Draw floor
		for (int y = drawEnd; y < 600; y++) {
			put_pixel_on_img(data, intopos(x, y), 0x000000, img);
		}
	}
}


int	render_frame(t_data *data)
{
	t_img	img;

	img.width = 800;
	img.heigth = 600;
	img.img = mlx_new_image(data->mlx, img.width, img.heigth);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, \
	&img.line_length, &img.endian);
	// mlx_clear_window(data->mlx, data->win);
	perform_raycasting(data, &img);
	render_mini_map(data, &img);
	mlx_put_image_to_window(data->mlx, data->win, img.img, 0, 0);
	mlx_destroy_image(data->mlx, img.img);
	return (0);
}


