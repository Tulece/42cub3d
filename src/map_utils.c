/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anporced <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 02:04:56 by anporced          #+#    #+#             */
/*   Updated: 2024/08/08 02:04:58 by anporced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	get_file_size(t_data *data)
{
	int		fd;
	int		size;
	char	c;

	fd = open(data->map.map_path, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("An error occured while opening the map.\n", 2);
		quit_early(data);
	}
	size = 0;
	while (read(fd, &c, 1) > 0)
		size++;
	if (read(fd, &c, 1) == -1)
	{
		ft_putstr_fd("An error occured while reading the map.\n", 2);
		quit_early(data);
	}
	close(fd);
	return (size);
}

char	*file_to_str(t_data *data)
{
	int		fd;
	char	*str;
	int		i;

	str = malloc(sizeof(char) * (get_file_size(data) + 1));
	if (!str)
		ft_putstr_fd("An error occured with malloc.\n", 2);
	fd = open(data->map.map_path, O_RDONLY);
	if (fd == -1)
		return ("");
	i = 0;
	while (read(fd, &str[i], 1) > 0)
		i++;
	str[i] = '\0';
	close(fd);
	return (str);
}

char	**str_to_tab(char *str)
{
	char	**map;

	map = ft_split(str, '\n');
	free(str);
	return (map);
}

void	fill_lines(t_axes size, t_data *data)
{
	int		i;
	int		j;
	char	*nl;

	i = 0;
	while (i < size.y)
	{
		j = 0;
		nl = malloc(size.x + 1);
		while (data->map.map[i][j])
		{
			nl[j] = data->map.map[i][j];
			j++;
		}
		while (j < size.x)
		{
			nl[j] = ' ';
			j++;
		}
		nl[j] = '\0';
		free(data->map.map[i]);
		data->map.map[i] = nl;
		i++;
	}
}

void	display_map_in_terminal(t_data *data)
{
	int	i;

	if (!data->map.map)
	{
		ft_printf("No map loaded.\n");
		return ;
	}
	i = -1;
	while (++i < data->map.map_dim.y)
		ft_printf("%s\n", data->map.map[i]);
}
