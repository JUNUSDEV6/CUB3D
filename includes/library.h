/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   library.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdendonc <rdendonc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:28:12 by rdendonc          #+#    #+#             */
/*   Updated: 2024/09/25 11:28:13 by rdendonc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBRARY_H
# define LIBRARY_H

# define BUFFER_SIZE 3

# define MLX_ERROR 1

# define X_EVENT_KEY_PRESS	2
# define X_EVENT_KEY_EXIT	17

/*
** Keyboard & ARROWS
*/

# define K_AR_L 123
# define K_AR_R 124

# define K_A 0
# define K_D 2
# define K_W 13
# define K_S 1
# define K_ESC 53
# define K_TAB 48

/*
** Mouse
*/

# define M_CLK_L 1
# define M_CLK_R 3
# define M_CLK_M 2
# define M_SCR_U 4
# define M_SCR_D 5

# define KEY_ESC 53
# define KEY_W 13
# define KEY_S 1
# define KEY_A 0
# define KEY_D 2

# define GO_UP 1
# define GO_DOWN 2
# define GO_LEFT 3
# define GO_RIGHT 4

# include "libft.h"
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <math.h>
# include <stdbool.h>

# define WIDTH 640
# define HEIGHT 480
# define TEXWIDTH 64
# define TEXHEIGHT 64

typedef struct s_raycst
{
	double			camera_x;
	double			ray_dir_x;
	double			ray_dir_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			wall_dist;
	double			wall_x;
	double			step;
	double			tex_pos;
	int				map_x;
	int				map_y;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
	int				line_height;
	int				draw_start;
	int				draw_end;
	int				tex_n;
	int				tex_x;
	int				tex_y;
	int				x;
	unsigned int	color;
}				t_raycst;

typedef struct s_img
{
	void	*img_ptr;
	char	*pixels_ptr;
	int		bpp;
	int		endian;
	int		line_leng;
}			t_img;

typedef struct s_cub
{
	int		fd_cub;
	char	**cub;
	void	*mlx_ptr;
	void	*mlx_window;
	void	*mlx_img;
	int		*img_data;
	int		*textures[4];
	void	*no_txr;
	void	*so_txr;
	void	*we_txr;
	void	*ea_txr;
	int		f_color;
	int		c_color;
	int		img_w;
	int		img_h;
	char	**map;
	int		**m;
	int		start_i;
	int		start_j;
	char	start_dir;
	t_img	img;
	double	posx;
	double	posy;
	double	dirx;
	double	diry;
	double	planex;
	double	planey;
	double	m_s;
	double	r_s;
	int		width_m;
	int		height_m;
}	t_cub;

// -------------------------------- PARSING -------------------------------- //
/* check_map */
int				check_map(t_cub *cub, char **map, int length);
/* get_colors */
void			get_colors(t_cub *cub);
/* get_textures */
int				get_textures(t_cub *cub);
/* main_parsing */
int				main_parsing(t_cub *cub, int argc, char **argv);
/* parsing_colors */
char			**create_colors_tab(char **cub, int i);
int				parsing_colors(char **cub);
/* parsing_doubles */
int				double_infos(char **cub);
/* parsing_elements */
int				missing_element(char **cub);
/* parsing_floating */
int				floating_elements(char **cub);
/* parsing_map */
int				parsing_map(t_cub *cub);
/* parsing_texture */
char			*find_path(char **cub, char *dir, char *path, char **tab);
int				parsing_textures(t_cub *cub);

// ------------------------------ RAYCASTING ------------------------------ //
/* init_mlx */
void			init_game(t_cub *cub);
void			init_data(t_cub *cub);
/* raycasting */
void			setup_raycasting(t_cub *cub, t_raycst *raycst);
unsigned int	get_pixel_color(t_cub *cub, int texture_index, int x, int y);
void			draw_textures(t_cub *cub, t_raycst *raycst, int i, int y);

// -------------------------------- SRC -------------------------------- //
/* main */
int				error(char *msg);
int				main(int argc, char **argv);
/* utils */
void			ft_exit(t_cub *cub, char *msg, int code);
void			free_tab(char **tab);
void			free_all(t_cub *cub);
void			print_tab(char **tab);

#endif
