#include "../includes/cub3d.h"

int	get_file_size(t_data *data)
{
	int		fd;
	int		size;
	char	c;

	fd = open(data->map.map_path, O_RDONLY);
		printf("%s\n", data->map.map_path);
	if (fd == -1)
	{
		ft_printf("An error occured while opening the map.\n");
		quit(data);
	}
	size = 0;
	while (read(fd, &c, 1) > 0)
		size++;
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
		ft_printf("An error occured with malloc.\n");
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
	return (size);
}

void display_map_in_terminal(t_data *data)
{
	int i;

	if (!data->map.map)
	{
		ft_printf("No map loaded.\n");
		return;
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
			break; // Si la ligne commence par un chiffre, on considère que c'est une ligne de la carte
		else
		{
			ft_printf("Error: Invalid line detected: %s\n", lines[i]);
			quit(data);
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
				return (0);
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
	if (dir == 'E')
		i = 90.0;
	if (dir == 'S')
		i = 180.0;
	if (dir == 'W')
		i = 270.0;
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
				data->player.x = j;
				data->player.y = i;
				set_deg_dir(data, map[i][j]);
			}
			j++;
		}
		i++;
	}
}

void init_map(t_data *data)
{
	char	*file_content;
	char	**lines;
	int		i;
	int		map_start_index;

	file_content = file_to_str(data);
	lines = ft_split(file_content, '\n');
	free(file_content);
	map_start_index = parse_texture_paths(data, lines);
	data->map.map = &lines[map_start_index];
	printf("NO = %s\nSO = %s\nWE = %s\nEA = %s\n", data->texture.no_texture.path, data->texture.so_texture.path, data->texture.we_texture.path, data->texture.ea_texture.path);
	if (!validate_map(data->map.map))
	{
		ft_printf("Error: Invalid map character detected.\n");
		i = -1;
		while (lines[++i])
			free(lines[i]);
		free(lines);
		quit(data);
	}
	data->map.map_dim = map_size(data);
	locate_player(data);
	printf("floor color = %s\nceiling color = %s\n", data->texture.floor_color, data->texture.ceiling_color);
	printf("map_dim.x = %d\nmap_dim.y = %d\n", data->map.map_dim.x, data->map.map_dim.y);
	display_map_in_terminal(data);
	i = -1;
}

// void	display_map(t_data *data, t_axes i)
// {
// 	if (data->map.map[i.y][i.x] == '1')

// 	else if (data->map.map[i.y][i.x] == '0')
// }
