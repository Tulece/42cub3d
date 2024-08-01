#include "../includes/cub3d.h"
#include "../includes/structs.h"

int x_off(t_data *data)
{
    int offset;

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
    return offset;
}

int y_off(t_data *data)
{
    int offset;

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
    return offset;
}

t_axes offset_mm(t_data *data, t_axes src)
{
    t_axes pos;

    pos.x = src.x - x_off(data);
    pos.y = src.y - y_off(data);
    return pos;
}

void	put_pixel_on_img(t_data *data, t_axes pos, int color, t_img *img)
{
	int pixel;

	pixel = (pos.x * 4) + (pos.y * img->line_length);
    img->addr[pixel] = color & 0xFF; // Blue
    img->addr[pixel + 1] = (color >> 8) & 0xFF; // Green
    img->addr[pixel + 2] = (color >> 16) & 0xFF; // Red
    img->addr[pixel + 3] = (color >> 24) & 0xFF;
}

void put_pixel_on_img_offset(t_data *data, t_axes pos, int color, t_img *img)
{
    t_axes mm_pos;
    t_axes tile_pos;

    // Convertir les coordonnées de pixels en coordonnées de tuile
    tile_pos.x = pos.x / TILE_SIZE;
    tile_pos.y = pos.y / TILE_SIZE;

    // Appliquer l'offset pour obtenir la position sur la minimap
    mm_pos = offset_mm(data, tile_pos);
    mm_pos.x *= TILE_SIZE;
    mm_pos.y *= TILE_SIZE;

    // Ajouter la position dans la tuile
    mm_pos.x += pos.x % TILE_SIZE;
    mm_pos.y += pos.y % TILE_SIZE;

    // Dessiner le pixel sur l'image
    put_pixel_on_img(data, mm_pos, color, img);
}

void draw_tile(t_data *data, t_axes pos, int color, t_img *img)
{
    t_axes pix_pos;

    for (int i = 0; i < TILE_SIZE; i++)
    {
        for (int j = 0; j < TILE_SIZE; j++)
        {
            pix_pos.x = (pos.x * TILE_SIZE) + j;
            pix_pos.y = (pos.y * TILE_SIZE) + i;
            put_pixel_on_img(data, pix_pos, color, img);
        }
    }
}

void draw_map(t_data *data, t_img *img)
{
    t_axes pos;
    t_axes p_pos;

    for (pos.y = 0; pos.y < MM_SIZE; pos.y++)
    {
        for (pos.x = 0; pos.x < MM_SIZE; pos.x++)
        {
            p_pos.x = x_off(data) + pos.x;
            p_pos.y = y_off(data) + pos.y;
            
            if (p_pos.x >= 0 && p_pos.x < data->map.map_dim.x && p_pos.y >= 0 && p_pos.y < data->map.map_dim.y)
            {
                if (data->map.map[p_pos.y][p_pos.x] == '1')
                    draw_tile(data, pos, 0xFFFFFF, img);
                else
                    draw_tile(data, pos, 0x000000, img);
            }
            else
            {
                draw_tile(data, pos, 0x555555, img); // Optional: Out of bounds area
            }
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
	while (i < 70)
	{
		j = 0;
		angle = degrad(data->player.deg_dir - 34 + (i * (44.0 / 45))); // Ajustement de l'angle
		while (j < 35)
		{
			pos.x = (int)(data->player.x * TILE_SIZE + j * cos(angle));
			pos.y = (int)(data->player.y * TILE_SIZE + j * sin(angle));
			if (!is_collision(data, pos.x / TILE_SIZE, pos.y / TILE_SIZE))
			{
				put_pixel_on_img_offset(data, pos, 0xFF0000, img);
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

void draw_image_in_image(t_img *src, t_img *dst, t_axes pos)
{
    int x, y;
    int pixel_src, pixel_dst;

    for (y = 0; y < src->heigth; y++)
    {
        for (x = 0; x < src->width; x++)
        {
            pixel_src = y * src->line_length + x * (src->bpp / 8);
            pixel_dst = (pos.y + y) * dst->line_length + (pos.x + x) * (dst->bpp / 8);

            dst->addr[pixel_dst] = src->addr[pixel_src];       // Blue
            dst->addr[pixel_dst + 1] = src->addr[pixel_src + 1]; // Green
            dst->addr[pixel_dst + 2] = src->addr[pixel_src + 2]; // Red
            dst->addr[pixel_dst + 3] = src->addr[pixel_src + 3]; // Alpha (if any)
        }
    }
}

void    render_mini_map(t_data *data, t_img *frame)
{
	t_img	img;

	img.width = MM_SIZE * TILE_SIZE;
	img.heigth = MM_SIZE * TILE_SIZE;
	img.img = mlx_new_image(data->mlx, img.width, img.heigth);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_length, &img.endian);
	draw_map(data, &img);
	draw_player(data, &img);
	draw_image_in_image(&img, frame, intopos(0,0));
	mlx_destroy_image(data->mlx, img.img);
}
