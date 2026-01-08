/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alcarril.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 03:14:57 by alejandro         #+#    #+#             */
/*   Updated: 2026/01/08 15:05:00 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef ALCARRIL_H
# define ALCARRIL_H

/*
	LIBRERIAS:
*/


# include <stdbool.h>

/*
	DEFINES:
*/

# define WIDTH 720
# define HEIGHT 720

#define WIN_SCALE 10

# define MAX_COLUMS 20
# define MAX_ROWS 15

#define MINI_WIDTH 4
#define MINI_HEIGHT 4

# define WALL 1
# define FLOOR 0

# define X 1
# define Y 0

#define VERTICAL 1
#define HORIZONTAL 0

# define PI 3.14159265
# define EPSILON 0.15f
# define FRICTION 0.7f

/*
	STRUCTS:
*/


typedef struct	s_player_data
{
	float	pos_x;
	float	pos_y;
	float	angle;
	float	rad_angle;
	float	speed;
	float	r_speed;
	float	volume;

	// on/off keys
	bool	move_up;
	bool	move_down;
	bool	move_left;
	bool	move_right;
	bool	r_counterclockwise;
	bool	r_clockwise;
	bool	sprint;

	//cvision data
	float	fov;
	float	rad_fov;
}	t_player;

typedef struct	s_map
{
	unsigned int	max_columns; //x
	unsigned int	max_rows; //y
	char map_grids[MAX_ROWS][MAX_COLUMS];
	//colors
	//textures
}	t_map;

//crear la strcutura frame para cuidar la memeria en cada frame no usar memeria local
typedef struct	s_frame_data
{	
	//minimap
	float	mm_height;
	float	mm_widht;
	float	mm_scale[2];
	bool	minimap_onoff;
	bool	minimap_showrays;
	
	//estras minimapa
	//minimap zoom
	//minimap traslation
	//on /off mouse //esta quizas no vaya aqui
	//rotaciones minimapa
	//rueda de raton para zoom minimapa

	//Raycasting config
	bool	raycasting_onoff;
	bool	fish_eye;//
	bool	euclidean;//quizas sobre
	
	float	*fov_distances; // Array de distancias hasta las paredes quizas osbre
	
}	t_frame;

typedef struct	s_mlx_api_components
{
	//mlx components
	void	*mlx_var;
	void	*mlx_window;
	void	*mlx_img;
	char	*win_name;
	
	//window data
	int		win_height;
	int		win_width;

	//image data
	char	*bit_map_address;
	char	*bit_map_address_copy;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	
	//game components
	t_player	*player;
	t_map		*map;
	t_frame		*frame;
}	t_mlx;


typedef struct	s_ray
{
	float			raydir[2];
	float			delta[2];
	float			sidedist[2];
	int				map[2];
	unsigned int	step[2];
	float			perp_wall_dist;
}	t_ray;


/*
	FUNCTION PROTOTIPES:
*/

//Initializations
char	init_mlx_components(t_mlx *mlx);
void	setup_window_wh(t_mlx *mlx);
void	destroy_mlx_componets(int (*f)(), int (*g)(), int (*t)(), t_mlx *mlx);
void	setup_player(t_mlx *mlx);
void	init_player_orientation_pos(t_player *pl, char cardinal, int pos[2]);
void	init_frame_data( t_mlx *mlx);
void	get_minimapscale(t_mlx *mlx, float *scale);

//hooks and events
void	create_hooks(t_mlx *mlx);
int		key_press(int keysym, t_mlx *mlx);
void	player_keypress(t_mlx *mlx, int keysym);
void	change_fov(t_mlx *mlx);
void	toogle_raycasting(t_mlx *mlx);
void	toggle_minimap(t_mlx *mlx);
void	toggle_rays(t_mlx *mlx);
void	toggle_fish_eye(t_mlx *mlx);
int		key_release(int keysym, t_mlx *mlx);
int		close_handler(t_mlx *mlx);

//player move
bool	is_collision(float x, float y, t_mlx *mlx, float e);
void	rotate_player(t_mlx *mlx, float grados);
void	vectorization(t_mlx *mlx, t_player *player, float *diferencial);
void	move_player(t_mlx *mlx);
int		mouse_move(int x, int y, t_mlx *mlx);

//render
int		game_engine(t_mlx *mlx);

//render utils
void	buffering_pixel(int x, int y, t_mlx *mlx, int color);

//raycasting
void	throw_rays(t_mlx *mlx);
void	cast_ray(t_mlx *mlx, int n_rays, float ray_angle);

//render minimap 2D
int		render_frame2D(t_mlx *mlx);
void	draw_mini_pixel(t_mlx *mlx, int *win);
bool	is_wall(t_mlx *mlx, float *map);
void	is_person2D(t_mlx *mlx, int *window, float *map);
// void	draw_person2D(t_mlx *mlx);
bool	is_minimapzone(int win_x, int win_y, t_mlx *mlx);

//render rays 2D
void	draw_rays2D(t_mlx *mlx);
void	draw_ray2D(t_mlx *mlx, float diferencial[2], float rad);
bool	touch_wall(t_mlx *mlx, float x, float y);





#endif