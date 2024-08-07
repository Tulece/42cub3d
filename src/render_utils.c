#include "../includes/cub3d.h"

t_axes	intopos(int x, int y)
{
	t_axes	pos;

	pos.x = x;
	pos.y = y;
	return (pos);
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

void	calculate_line_height_and_draw_positions(t_ray *ray, int screen_height)
{
	ray->line_height = (int)(screen_height / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + screen_height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + screen_height / 2;
	if (ray->draw_end >= screen_height)
		ray->draw_end = screen_height - 1;
}
