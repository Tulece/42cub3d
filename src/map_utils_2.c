/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anporced <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 02:04:50 by anporced          #+#    #+#             */
/*   Updated: 2024/08/08 02:04:51 by anporced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_axes	map_size(t_data *data)
{
	t_axes	size;
	int		len;

	size.y = 0;
	size.x = 0;
	while (data->map.map[size.y])
	{
		len = ft_strlen(data->map.map[size.y]);
		if (len > size.x)
			size.x = len;
		size.y++;
	}
	fill_lines(size, data);
	return (size);
}

char	**dup_tab(char **tab)
{
	char	**new_tab;
	int		i;

	i = 0;
	while (tab[i])
		i++;
	new_tab = malloc((i + 1) * sizeof(char *));
	new_tab[i] = NULL;
	while (--i >= 0)
		new_tab[i] = ft_strdup(tab[i]);
	return (new_tab);
}
