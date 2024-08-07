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

int	validate_texture_paths(t_data *data)
{
	int	fd;

	fd = open(data->texture.no_texture.path, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error opening NO texture file", 2);
		return (0);
	}
	close(fd);
	fd = open(data->texture.so_texture.path, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error opening SO texture file", 2);
		return (0);
	}
	close(fd);
	fd = open(data->texture.we_texture.path, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error opening WE texture file", 2);
		return (0);
	}
	close(fd);
	fd = open(data->texture.ea_texture.path, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error opening EA texture file", 2);
		return (0);
	}
	close(fd);
	return (1);
}

void	handle_texture_error(t_data *data, char **lines)
{
	ft_putstr_fd("Error: Invalid line detected\n", 2);
	ft_free_tab(lines);
	free_text_paths(data);
	quit_early(data);
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
			break ;
		else
			handle_texture_error(data, lines);
	}
	return (i);
}

int is_valid_map_char(char c)
{
	if (!(c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == ' '))
	{
		ft_putstr_fd("Error: Invalid map character detected.\n", 2);
		return (0);
	}
	return (1);
}

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


void	handle_missing_info(t_data *data, char **lines)
{
	if (!data->texture.ea_texture.path || !data->texture.we_texture.path
		|| !data->texture.no_texture.path || !data->texture.so_texture.path
		|| !data->texture.floor_color || !data->texture.ceiling_color)
	{
		ft_printf("Error: Missing map information\n");
		ft_free_tab(lines);
		free_text_paths(data);
		quit_early(data);
	}
}

void	handle_invalid_paths(t_data *data, char **lines)
{
	if (!validate_texture_paths(data))
	{
		ft_free_tab(lines);
		free_text_paths(data);
		quit_early(data);
	}
}

void	initialize_map(t_data *data, char **lines, int map_start_index)
{
	data->map.map = dup_tab(&lines[map_start_index]);
	ft_free_tab(lines);
	data->map.map_dim = map_size(data);
}

void	handle_invalid_map(t_data *data)
{
	if (!validate_map(data))
	{
		free_text_paths(data);
		quit_early(data);
	}
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

void	init_map(t_data *data)
{
	char	*file_content;
	char	**lines;
	int		map_start_index;

	file_content = file_to_str(data);
	lines = ft_split(file_content, '\n');
	free(file_content);
	map_start_index = parse_texture_paths(data, lines);
	handle_missing_info(data, lines);
	handle_invalid_paths(data, lines);
	initialize_map(data, lines, map_start_index);
	handle_invalid_map(data);
	locate_player(data);
	set_colors(data);
}
