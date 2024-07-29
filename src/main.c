#include "../includes/cub3d.h"

int main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		error_exit("Usage: ./cub3D <map.cub>", NULL);
	init_data(&data);
	data.map.map_path = ft_strdup(argv[1]);
	init_map(&data);
	// init_textures(&data);
	// init_colors(&data);
	mlx_hook(data.win, 2, 1L<<0, handle_keypress, &data);
	mlx_hook(data.win, 3, 1L<<1, handle_keyrelease, &data);
	mlx_hook(data.win, 17, 0, cross_quit, &data);
	mlx_loop_hook(data.mlx, render_frame, &data);
	mlx_do_key_autorepeaton(data.mlx);
	mlx_loop(data.mlx);
	// cleanup(&data);
	return (0);
}
