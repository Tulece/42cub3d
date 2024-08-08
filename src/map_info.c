/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anporced <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 02:04:31 by anporced          #+#    #+#             */
/*   Updated: 2024/08/08 02:04:35 by anporced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	get_color(char *color_char)
{
	char	**colors;
	int		color;
	int		i;

	color = 0;
	i = 0;
	colors = ft_split(color_char, ',');
	if (!colors)
	{
		ft_putstr_fd("Error: Failed to split color string\n", 2);
		return (-1);
	}
	while (i < 3)
	{
		if (colors[i] == NULL || str_is_digit(colors[i]) \
		|| ft_atoi(colors[i]) > 255 || ft_atoi(colors[i]) < 0)
		{
			ft_free_tab(colors);
			return (-1);
		}
		color += ft_atoi(colors[i]) << (3 - (i + 1)) * 8;
		i++;
	}
	ft_free_tab(colors);
	return (color);
}

void	set_colors(t_data *data)
{
	if (data->texture.floor_color)
		data->texture.floor = get_color(data->texture.floor_color);
	if (data->texture.ceiling_color)
		data->texture.ceiling = get_color(data->texture.ceiling_color);
	if (data->texture.ceiling == -1 || data->texture.floor == -1)
	{
		ft_putstr_fd("Error: Invalid color detected\n", 2);
		free_text_paths(data);
		quit_early(data);
	}
}

void	set_deg_dir(t_data *data, char dir)
{
	double	i;

	i = 0.0;
	if (dir == 'N')
		i = 270.0;
	if (dir == 'W')
		i = 180.0;
	if (dir == 'S')
		i = 90.0;
	data->player.deg_dir = i;
}

void	locate_player(t_data *data)
{
	char	**map;
	int		i;
	int		j;

	map = data->map.map;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'E' || map[i][j] == 'S' \
			|| map[i][j] == 'W')
			{
				data->player.x = j + 0.5;
				data->player.y = i + 0.5;
				set_deg_dir(data, map[i][j]);
				map[i][j] = '0';
			}
			j++;
		}
		i++;
	}
	calculate_vectors(&data->player);
}
