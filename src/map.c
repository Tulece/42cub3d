/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anporced <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 02:05:00 by anporced          #+#    #+#             */
/*   Updated: 2024/08/08 02:05:04 by anporced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

void	handle_invalid_map(t_data *data)
{
	if (!validate_map(data))
	{
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
