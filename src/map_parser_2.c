/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anporced <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 02:04:39 by anporced          #+#    #+#             */
/*   Updated: 2024/08/08 02:04:48 by anporced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	neighbour_zero(t_data *data, int i, int j)
{
	if (i > 0 && data->map.map[i - 1][j] == '0')
		return (1);
	if (i < data->map.map_dim.y - 1 && data->map.map[i + 1][j] == '0')
		return (1);
	if (j > 0 && data->map.map[i][j - 1] == '0')
		return (1);
	if (j < data->map.map_dim.x - 1 && data->map.map[i][j + 1] == '0')
		return (1);
	return (0);
}

int	not_closed(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->map.map_dim.y)
	{
		j = 0;
		while (j < data->map.map_dim.x)
		{
			if (((i == 0 || i == data->map.map_dim.y - 1 || j == 0 \
			|| j == data->map.map_dim.x - 1) && data->map.map[i][j] == '0') \
			|| (data->map.map[i][j] == ' ' && neighbour_zero(data, i, j)))
			{
				ft_putstr_fd("Error: Map not closed\n", 2);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	validate_map(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map.map[i])
	{
		j = 0;
		while (data->map.map[i][j])
		{
			if (!is_valid_map_char(data->map.map[i][j]) || not_closed(data))
			{
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}
