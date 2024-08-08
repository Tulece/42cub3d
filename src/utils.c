/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anporced <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 02:05:11 by anporced          #+#    #+#             */
/*   Updated: 2024/08/08 02:08:26 by anporced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_walkable(char **map, int x, int y)
{
	return (map[y][x] == '0');
}

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	str_is_digit(char *str)
{
	while (*str)
	{
		if ((*str < '0' || *str > '9'))
		{
			return (1);
		}
		str++;
	}
	return (0);
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
