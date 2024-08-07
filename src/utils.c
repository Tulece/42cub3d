#include "../includes/cub3d.h"

int	is_walkable(char **map, int x, int y)
{
	return (map[y][x] == '0');
}

void	error_exit(const char *message, t_data *data)
{
	fprintf(stderr, "Error\n%s\n", message);
	exit(1);
}

void	put_pixel_on_img(t_data *data, t_axes pos, int color, t_img *img)
{
	int	pixel;

	pixel = (pos.x * 4) + (pos.y * img->line_length);
	img->addr[pixel] = color & 0xFF;
	img->addr[pixel + 1] = (color >> 8) & 0xFF;
	img->addr[pixel + 2] = (color >> 16) & 0xFF;
	img->addr[pixel + 3] = (color >> 24) & 0xFF;
}
