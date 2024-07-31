#include "../includes/cub3d.h"

void perform_raycasting(t_data *data) {
    for (int x = 0; x < 800; x++) { // Supposons une largeur d'écran de 800
        double cameraX = 2 * x / 800.0 - 1;
        double rayDirX = data->player.dir_x + data->player.plane_x * cameraX;
        double rayDirY = data->player.dir_y + data->player.plane_y * cameraX;

        int mapX = (int)data->player.x;
        int mapY = (int)data->player.y;

        double sideDistX;
        double sideDistY;

        double deltaDistX = fabs(1 / rayDirX);
        double deltaDistY = fabs(1 / rayDirY);
        double perpWallDist;

        int stepX;
        int stepY;

        int hit = 0;
        int side;

        if (rayDirX < 0) {
            stepX = -1;
            sideDistX = (data->player.x - mapX) * deltaDistX;
        } else {
            stepX = 1;
            sideDistX = (mapX + 1.0 - data->player.x) * deltaDistX;
        }
        if (rayDirY < 0) {
            stepY = -1;
            sideDistY = (data->player.y - mapY) * deltaDistY;
        } else {
            stepY = 1;
            sideDistY = (mapY + 1.0 - data->player.y) * deltaDistY;
        }

        while (hit == 0) {
            if (sideDistX < sideDistY) {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            } else {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            if (data->map.map[mapY][mapX] > '0') hit = 1;
        }

        if (side == 0) perpWallDist = (mapX - data->player.x + (1 - stepX) / 2) / rayDirX;
        else perpWallDist = (mapY - data->player.y + (1 - stepY) / 2) / rayDirY;

        int lineHeight = (int)(600 / perpWallDist);

        int drawStart = -lineHeight / 2 + 600 / 2;
        if (drawStart < 0) drawStart = 0;
        int drawEnd = lineHeight / 2 + 600 / 2;
        if (drawEnd >= 600) drawEnd = 600 - 1;
  		for (int y = 0; y < drawStart; y++) {
            mlx_pixel_put(data->mlx, data->win, x, y, 0x000000);
        }
        int color = (side == 1) ? 0xAAAAAA : 0xFFFFFF;

        for (int y = drawStart; y < drawEnd; y++) {
            mlx_pixel_put(data->mlx, data->win, x, y, color);
        }
    }
}

int render_frame(t_data *data)
{
	// mlx_clear_window(data->mlx, data->win);
	perform_raycasting(data);
	draw_map(data);
	draw_player(data);
	return (0);
}


