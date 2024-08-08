#include "../includes/cub3d.h"

int	validate_texture_paths(t_data *data)
{
	int	fd;

	fd = open(data->texture.no_texture.path, O_RDONLY);
	if (fd == -1)
		return (ft_putstr_fd("Error opening NO texture file", 2), 0);
	close(fd);
	fd = open(data->texture.so_texture.path, O_RDONLY);
	if (fd == -1)
		return (ft_putstr_fd("Error opening SO texture file", 2), 0);
	close(fd);
	fd = open(data->texture.we_texture.path, O_RDONLY);
	if (fd == -1)
		return (ft_putstr_fd("Error opening WE texture file", 2), 0);
	close(fd);
	fd = open(data->texture.ea_texture.path, O_RDONLY);
	if (fd == -1)
		return (ft_putstr_fd("Error opening EA texture file", 2), 0);
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

int	is_valid_map_char(char c)
{
	if (!(c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' \
	|| c == 'W' || c == ' '))
	{
		ft_putstr_fd("Error: Invalid map character detected.\n", 2);
		return (0);
	}
	return (1);
}
