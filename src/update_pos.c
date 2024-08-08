/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_pos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgibert <tgibert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 02:04:32 by tgibert           #+#    #+#             */
/*   Updated: 2024/08/08 02:04:34 by tgibert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../includes/structs.h"

void	calculate_direction_0(t_data *data, int run, double *d_x, double *d_y)
{
	*d_x = (data->player.speed * (1 + run)) \
		* cos(degrad(data->player.deg_dir));
	*d_y = (data->player.speed * (1 + run)) \
		* sin(degrad(data->player.deg_dir));
}

void	calculate_direction_1(t_data *data, int run, double *d_x, double *d_y)
{
	*d_x = (-data->player.speed * (1 + run)) \
		* cos(degrad(data->player.deg_dir));
	*d_y = (-data->player.speed * (1 + run)) \
		* sin(degrad(data->player.deg_dir));
}

void	calculate_direction_2(t_data *data, int run, double *d_x, double *d_y)
{
	*d_x = (-data->player.speed * (1 + run)) \
		* sin(degrad(data->player.deg_dir));
	*d_y = (data->player.speed * (1 + run)) \
		* cos(degrad(data->player.deg_dir));
}

void	calculate_direction_3(t_data *data, int run, double *d_x, double *d_y)
{
	*d_x = (data->player.speed * (1 + run)) \
		* sin(degrad(data->player.deg_dir));
	*d_y = (-data->player.speed * (1 + run)) \
		* cos(degrad(data->player.deg_dir));
}

void	update_player_position_2(t_data *data, int dir, int run)
{
	double	d_x;
	double	d_y;

	d_x = 0.0;
	d_y = 0.0;
	if (dir == 0)
		calculate_direction_0(data, run, &d_x, &d_y);
	else if (dir == 1)
		calculate_direction_1(data, run, &d_x, &d_y);
	else if (dir == 2)
		calculate_direction_2(data, run, &d_x, &d_y);
	else if (dir == 3)
		calculate_direction_3(data, run, &d_x, &d_y);
	update_player_position(data, d_x, d_y);
}
