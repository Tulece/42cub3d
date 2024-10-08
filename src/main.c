/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anporced <anporced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 02:04:26 by anporced          #+#    #+#             */
/*   Updated: 2024/08/08 16:03:40 by anporced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2 || !ft_strncmp(&(argv[1][ft_strlen(argv[1]) - 5]), ".cub", 4))
		return (ft_putstr_fd("Usage: ./cub3D <map.cub>\n", 2), 1);
	init_data(&data);
	data.map.map_path = ft_strdup(argv[1]);
	init_map(&data);
	init_textures(&data);
	mlx_hook(data.win, 2, 1L << 0, handle_keypress, &data);
	mlx_hook(data.win, 3, 1L << 1, handle_keyrelease, &data);
	mlx_hook(data.win, 17, 0, cross_quit, &data);
	mlx_loop_hook(data.mlx, render_frame, &data);
	mlx_do_key_autorepeatoff(data.mlx);
	mlx_loop(data.mlx);
	return (0);
}
