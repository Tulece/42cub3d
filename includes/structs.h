#ifndef STRUCTS_H
#define STRUCTS_H

typedef enum s_textures_index
{
	NO,
	SO,
	WE,
	EA
}	t_textures_index;

typedef struct s_axes
{
	int	x;
	int	y;
}	t_axes;

typedef struct s_img
{
	void	*img;
	char	*path;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}			t_img;

typedef struct s_texture
{
	t_img	no_texture;
	t_img	so_texture;
	t_img	we_texture;
	t_img	ea_texture;
	char	*floor_color;
	char	*ceiling_color;
}			t_texture;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	speed;
	double	deg_dir;
	double	pov_speed;
}			t_player;

typedef struct s_map
{
	char	**map;
	char	*map_path;
	t_axes	map_dim;
}			t_map;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	t_player	player;
	t_texture	texture;
	t_map		map;
}				t_data;

#endif
