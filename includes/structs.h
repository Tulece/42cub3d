#ifndef STRUCTS_H
# define STRUCTS_H

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
	int		width;
	int		heigth;
}			t_img;

typedef struct s_texture
{
	t_img	no_texture;
	t_img	so_texture;
	t_img	we_texture;
	t_img	ea_texture;
	int		floor;
	int		ceiling;
	char	*floor_color;
	char	*ceiling_color;
}			t_texture;

typedef struct s_ray
{
    double camera_x;
    double ray_dir_x;
    double ray_dir_y;
    int map_x;
    int map_y;
    double side_dist_x;
    double side_dist_y;
    double delta_dist_x;
    double delta_dist_y;
    double perp_wall_dist;
    int step_x;
    int step_y;
    int hit;
    int side;
    int line_height;
    int draw_start;
    int draw_end;
    t_img *texture;
    double wall_x;
    int tex_x;
    int tex_y;
    int color;
} t_ray;


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
	int			key_states[7];
	t_player	player;
	t_texture	texture;
	t_map		map;
}				t_data;

#endif
