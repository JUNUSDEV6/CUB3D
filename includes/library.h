#ifndef LIBRARY_H
# define LIBRARY_H

# include "libft.h"
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <math.h>
# include <string.h>
# include <stdbool.h>

# define width 640
# define height 480
#define X_EVENT_KEY_PRESS	2
#define X_EVENT_KEY_EXIT	17

# define K_A 0
# define K_B 11
# define K_C 8
# define K_D 2
# define K_E 14
# define K_F 3
# define K_G 5
# define K_H 4
# define K_I 34
# define K_J 38
# define K_K 40
# define K_L 37
# define K_M 46
# define K_N 45
# define K_O 31
# define K_P 35
# define K_Q 12
# define K_R 15
# define K_S 1
# define K_T 17
# define K_U 32
# define K_V 9
# define K_W 13
# define K_X 7
# define K_Y 16
# define K_Z 6

/*
** Keyboard ARROWS
*/

# define K_AR_L 123
# define K_AR_R 124
# define K_AR_U 126
# define K_AR_D 125

/*
** Keyboard NUMPAD
*/

# define K_NP_DIV 75
# define K_NP_MUL 67
# define K_NP_MIN 78
# define K_NP_PLU 69
# define K_NP_1	83
# define K_NP_2	84
# define K_NP_3	85
# define K_NP_4	86
# define K_NP_5	87
# define K_NP_6	88
# define K_NP_7	89
# define K_NP_8	91
# define K_NP_9	92

/*
** Keyboard MISC
*/

# define K_SP 49
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
	void	*no_txr;
	void	*so_txr;
	void	*we_txr;
	void	*ea_txr;
	char	*f_color;
	char	*c_color;
	char	**map;
	t_img	img;
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
	double	m_s;
	double	r_s;
}	t_cub;

typedef struct	s_raycst
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	per_wall_dist;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
}				t_raycst;

// -------------------------------- INIT & RENDER -------------------------------- //
void	init_cub(t_cub *cub);
// -------------------------------- PARSING -------------------------------- //
/* get_texture */
int		get_textures(t_cub *cub);
/* main_parsing */
int		main_parsing(t_cub *cub, int argc, char **argv);
/* parsing_colors */
int		parsing_colors(char **cub);
/* parsing_doubles */
int		double_infos(char **cub);
/* parsing_elements */
int		missing_element(char **cub);

// -------------------------------- SRC -------------------------------- //
/* main */
int		error(char *msg);
int		main(int argc, char **argv);
/* utils */
void	free_tab(char **tab);
void	free_all(t_cub *cub);
void	print_tab(char **tab);

#endif
