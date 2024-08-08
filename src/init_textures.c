/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anporced <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 02:04:18 by anporced          #+#    #+#             */
/*   Updated: 2024/08/08 02:04:19 by anporced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_no_texture(t_data *data)
{
	init_single_texture(data, &data->texture.no_texture);
}

void	init_so_texture(t_data *data)
{
	init_single_texture(data, &data->texture.so_texture);
}

void	init_we_texture(t_data *data)
{
	init_single_texture(data, &data->texture.we_texture);
}

void	init_ea_texture(t_data *data)
{
	init_single_texture(data, &data->texture.ea_texture);
}

void	init_textures(t_data *data)
{
	init_no_texture(data);
	init_so_texture(data);
	init_we_texture(data);
	init_ea_texture(data);
}
