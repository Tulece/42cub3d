#ifndef CUB3D_H
# define CUB3D_H

# ifdef __APPLE__
#  include <ApplicationServices/ApplicationServices.h>
# endif
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_R_ARROW 65363
# define KEY_L_ARROW 65361

# define KEY_W_I 0
# define KEY_A_I 1
# define KEY_S_I 2
# define KEY_D_I 3
# define KEY_R_ARROW_I 4
# define KEY_L_ARROW_I 5
# define KEY_SHIFT_I 6

# define KEY_ESC 65307
# define PI 3.14159265358979323846

# include "../libft/includes/libft.h"
# include "../libft/includes/ft_printf.h"
# include "../minilibx-linux/mlx.h"
# include "structs.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <errno.h>
# include <math.h>

# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_SHIFT 65505
# define MM_SIZE 12

# define TILE_SIZE 8

// Initialisation
void	init_data(t_data *data);
void	init_textures(t_data *data);
void	initialize_map(t_data *data, char **lines, int map_start_index);
void	init_map(t_data *data);
void	init_no_texture(t_data *data);
void	init_so_texture(t_data *data);
void	init_we_texture(t_data *data);
void	init_ea_texture(t_data *data);
void	init_single_texture(t_data *data, t_img *texture);
void	calculate_vectors(t_player *player);
void	initialize_ray(t_data *data, t_ray *ray, int x);

// keybinding.c
int		handle_keypress(int keycode, t_data *data);
int		handle_keyrelease(int keycode, t_data *data);

// img
void	update_player_position(t_data *data, double delta_x, double delta_y);
void	update_player_position_2(t_data *data, int dir, int run);
void	update_player_dir(t_data *data, int dir);
void	draw_player(t_data *data, t_img *img);
void	draw_map(t_data *data, t_img *img);

// map_info.c
int		get_color(char *color_char);
void	set_colors(t_data *data);
void	set_deg_dir(t_data *data, char dir);
int		locate_player(t_data *data);

// map_parser.c
int		validate_texture_paths(t_data *data);
void	handle_texture_error(t_data *data, char **lines);
int		parse_texture_paths(t_data *data, char **lines);
int		is_valid_map_char(char c);

// map_parser_2.c
int		neighbour_zero(t_data *data, int i, int j);
int		not_closed(t_data *data);
int		validate_map(t_data *data);

// map_utils.c
int		get_file_size(t_data *data);
char	*file_to_str(t_data *data);
char	**str_to_tab(char *str);
void	fill_lines(t_axes size, t_data *data);
void	display_map_in_terminal(t_data *data);

// map_utils_2.c
t_axes	map_size(t_data *data);
char	**dup_tab(char **tab);

// render_texture_utils.c
int		get_texture_color(t_img *texture, int x, int y);
void	select_texture(t_data *data, t_ray *ray);
void	calculate_wall_and_texture_x(t_data *data, t_ray *ray);
void	calculate_line_and_texture(t_data *data, t_ray *ray);

// render_utils.c
void	perform_dda(t_data *data, t_ray *ray);
void	calculate_step_and_initial_side_dist(t_data *data, t_ray *ray);
void	calculate_line_height_and_draw_positions(t_ray *ray, int screen_height);
t_axes	intopos(int x, int y);
void	perform_raycasting(t_data *data, t_img *img);

// render.c
int		render_frame(t_data *data);

// utils.c
int		is_walkable(char **map, int x, int y);
void	error_exit(const char *message, t_data *data);
void	ft_free_tab(char **tab);
int		str_is_digit(char *str);
void	put_pixel_on_img(t_data *data, t_axes pos, int color, t_img *img);

// img.c aussi
int		is_view_collision(t_data *data, double x, double y);

void	render_mini_map(t_data *data, t_img *img);
int		is_collision(t_data *data, double x, double y);

// exit.c
void	free_map(char **map);
void	free_text_paths(t_data *data);
int		quit_early(t_data *data);
int		cross_quit(t_data *data);
int		quit(t_data *data);

double	degrad(double deg);
void	put_pixel_on_img_offset(t_data *data, t_axes pos, int color,
			t_img *img);
int		x_off(t_data *data);
int		y_off(t_data *data);
void	draw_image_in_image(t_img *src, t_img *dst, t_axes pos);

#endif
