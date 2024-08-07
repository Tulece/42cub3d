#include "../includes/cub3d.h"

int	is_walkable(char **map, int x, int y)
{
	return (map[y][x] == '0');
}

void	error_exit(const char *message, t_data *data)
{
	fprintf(stderr, "Error\n%s\n", message);
	exit(1);
}
