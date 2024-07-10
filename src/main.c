#include "../includes/cub3d.h"

int	check_args(int ac, char **av)
{
	int	len;

	if (ac != 2)
		return (ft_printf("Add a map from /map folder to play.\n"));
	len = ft_strlen(av[1]) - 1;
	if (len <= 4)
		return (ft_printf("The map has to be a .cub file to play.\n"));
	if (av[1][len - 3] != '.' || av[1][len - 2] != 'c'
		|| av[1][len - 1] != 'u' || av[1][len] != 'b')
		return (ft_printf("The map has to be a .cub file and must exist to \
play.\n"));
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	// if (check_args(ac, av) != 0)
	// 	return (1);
	data.mlx = mlx_init;
	if (!data.mlx)
		return (1);
	// data.map.map_path = av[1];
	// textures and datas init here
	data.win = mlx_new_window(data.mlx, 300, 200, "cub3D");
	if (!data.win)
		return (1);
	// mlx_hook(data.win, 17, 0, cross_quit, &data);
	mlx_loop(data.mlx);
}
