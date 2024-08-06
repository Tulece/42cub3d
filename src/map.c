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

void display_map_in_terminal(t_data *data)
{
	int i;

	if (!data->map.map)
	{
		ft_printf("No map loaded.\n");
		return ;
	}
	i = -1;
	while (++i < data->map.map_dim.y)
		ft_printf("%s\n", data->map.map[i]);
}

int	parse_texture_paths(t_data *data, char **lines)
{
	int	i;

	i = -1;
	while (lines[++i])
	{
		if (ft_strncmp(lines[i], "NO ", 3) == 0)
			data->texture.no_texture.path = ft_strtrim(lines[i] + 3, " ");
		else if (ft_strncmp(lines[i], "SO ", 3) == 0)
			data->texture.so_texture.path = ft_strtrim(lines[i] + 3, " ");
		else if (ft_strncmp(lines[i], "WE ", 3) == 0)
			data->texture.we_texture.path = ft_strtrim(lines[i] + 3, " ");
		else if (ft_strncmp(lines[i], "EA ", 3) == 0)
			data->texture.ea_texture.path = ft_strtrim(lines[i] + 3, " ");
		else if (ft_strncmp(lines[i], "F ", 2) == 0)
			data->texture.floor_color = ft_strtrim(lines[i] + 2, " ");
		else if (ft_strncmp(lines[i], "C ", 2) == 0)
			data->texture.ceiling_color = ft_strtrim(lines[i] + 2, " ");
		else if (lines[i][0] >= '0' && lines[i][0] <= '9')
			break ; // Si la ligne commence par un chiffre, on considère que c'est une ligne de la carte a revoir donc
		else
		{
			ft_putstr_fd("Error: Invalid line detected\n", 2);
			quit_early(data);
		}
	}
	return (i);
}

int is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == ' ');
}

int validate_map(char **map)
{
	int i;
	int j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!is_valid_map_char(map[i][j]))
			{
				ft_printf("%c\n");
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
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
	char **map;
	int i;
	int j;

	map = data->map.map;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'E' || map[i][j] == 'S' || map[i][j] == 'W')
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

char **dup_tab(char **tab)
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

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	get_color(char *color_char)
{
	char	**colors;
	int		color;
	int		i;

	color = 0;
	i = 0;
	colors = ft_split(color_char, ',');
	while (i < 3)
	{
		color += ft_atoi(colors[i]) <<  (3 - (i + 1)) * 8;
		i++;
	}
	ft_free_tab(colors);
	return (color);
}

void init_map(t_data *data)
{
	char	*file_content;
	char	**lines;
	int		map_start_index;

	file_content = file_to_str(data);
	lines = ft_split(file_content, '\n');
	free(file_content);
	map_start_index = parse_texture_paths(data, lines);
	data->map.map = dup_tab(&lines[map_start_index]);
	ft_free_tab(lines);
	if (!validate_map(data->map.map))
	{
		ft_printf("Error: Invalid map character detected.\n");
		quit_early(data);
	}
	data->map.map_dim = map_size(data);
	locate_player(data);
	data->texture.floor = get_color(data->texture.floor_color);
	data->texture.ceiling = get_color(data->texture.ceiling_color);
	printf("floor color = %s\nceiling color = %s\n", data->texture.floor_color, data->texture.ceiling_color);
	printf("map_dim.x = %d\nmap_dim.y = %d\n", data->map.map_dim.x, data->map.map_dim.y);
	display_map_in_terminal(data);
}

// void	display_map(t_data *data, t_axes i)
// {
// 	if (data->map.map[i.y][i.x] == '1')

// 	else if (data->map.map[i.y][i.x] == '0')
// }
