#ifndef CUB3D_H
# define CUB3D_H

// # ifdef __linux__
// # include <X11/keysym.h>
// # include <X11/X.h>
// #  define KEY_Z 122
// #  define KEY_Q 113
// #  define KEY_S 115
// #  define KEY_D 100
// #  define ESC 65307
# ifdef __APPLE__
#  include <ApplicationServices/ApplicationServices.h>
# endif
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_R_ARROW 65363
# define KEY_L_ARROW 65361
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

# define TILE_SIZE 16

// Initialisation
void init_data(t_data *data);
void init_textures(t_data *data);
void	init_map(t_data *data);
void init_colors(t_data *data);

// Keybinding
int handle_keypress(int keycode, t_data *data);
int handle_keyrelease(int keycode, t_data *data);

// img
void	update_player_position(t_data *data, double delta_x, double delta_y);
void    update_player_position_2(t_data *data, int dir);
void    update_player_dir(t_data *data, int dir);
void	draw_player(t_data *data, t_img *img);
void	draw_map(t_data *data, t_img *img);


// Parsing
void parse_map(t_data *data, const char *map_path);

// Raycasting
void perform_raycasting(t_data *data, t_img *img);
void calculate_vectors(t_player *player);

// Events
int handle_keypress(int keycode, t_data *data);
int handle_keyrelease(int keycode, t_data *data);
int handle_exit(t_data *data);

// Rendering
int	render_frame(t_data *data);

// Utils
int is_walkable(char **map, int x, int y);
void error_exit(const char *message, t_data *data);

// Cleanup
void cleanup(t_data *data);




t_axes intopos(int x, int y);
void	put_pixel_on_img(t_data *data, t_axes pos, int color, t_img *img);
void    render_mini_map(t_data *data, t_img *img);
int is_collision(t_data *data, double x, double y);

// keybinding.c
int	hook_switch(int keycode, t_data *data);

// exit.c
int	quit(t_data *data);
int	cross_quit(t_data *data);

double	degrad(double deg);

#endif
