/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariani <mmariani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 14:15:25 by atarsi            #+#    #+#             */
/*   Updated: 2023/05/12 12:46:55 by mmariani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

#include "libft/libft.h"
#include "amlx/mlx.h"
// #include "minilibx/mlx.h"

#define PI 3.14159265359
#define RAD 0.0174533

#define FOV 60
#define HALF_FOV 30
#define FOV_R   60 * (PI/180)

#define ROT 0.03299066
#define HEIGHT	1024	// 2^10
#define WEIGHT	2048	// 2^11

//keypress
# define W		13
# define A		0
# define S		1
# define D		2
# define LEFT	123
# define RIGHT	124
# define ESC	53
# define SPEED	0.20
#define COLOR_PURPLE 16711935
#define COLOR_GREEN 65280
#define COLOR_BLUE 7190271

//texture
#define texWidth 64
#define texHeight 64

//wallpaper

# define WP		2383707

// typedef struct s_ray
// {
// 	float   x;         //origine X raggio
// 	float   y;         //origine Y raggio
// 	float   dist;      // distanza origine-muro raggio
// 	float	rayangle;
// }               t_ray;

typedef struct s_ray
{
    float   x;         //origine X raggio
    float   y;         //origine Y raggio
    float   dist;      // distanza origine-muro raggio
    float   wall;      // dimensione muro
    int     w_x;
}               t_ray;

typedef struct s_player
{
	float     x;
	float     y;
	int     w;
	int     a;
	int     s;
	int     d;
	float   dx;
	float   dy;
	float   angle;
	int     rigth;
	int     left;
}              t_player;

typedef struct s_image
{
	void    *img;
	int    *addr;
	int     l_bytes;
	int     bfp;
	int     endian;
}               t_image;

typedef struct s_img
{
	void    *img;
	char    *addr;
	int     l_bytes;
	int     bfp;
	int     endian;
}               t_img;

typedef struct s_casting
{
	t_ray	plane;
	int		**texture;
	int		**buf;

	
}               t_casting;

typedef struct s_map
{
	char	*north_texture_path;
	char	*south_texture_path;
	char	*west_texture_path;
	char	*east_texture_path;
	char	**map;
	int		mm_H;		//minimappsize(altezza)
	int		mm_W;		//minimappsize(larghezza)
	int		floor_color;
	int		ceiling_color;
}			t_map;


typedef struct s_cube3D
{
	char		*NO;
	char		*SO;
	char		*WE;
	char		*EA;
	char		*DO;
	int			F;
	int			C;
	int			row;		//numerorighemappa
	int			col;		//numerocolonnemappa
	// int			mm_H;		//minimappsize(altezza)
	// int			mm_W;		//minimappsize(larghezza)
	int			cH_size;		//cellamatricesize(altezza)
	int			cW_size;		//cellamatricesize(larghezza)
	int			cellsize;
	int			s_h;			//screensizealtezza
	int			s_w;			//screensizelarghezza
	//int		mini_cell_h;
	//int		mini_cell_w;
	void		*mlx;
	void		*win;
	// char		**map;
	int			frame;
	t_player	p;
	t_img		img;
	t_image		minimap;
	t_ray		ray;
	t_casting	raycast;
	t_map		map;
}				t_cube3D;



//init

void    ft_init_info(t_cube3D *data);
void    ft_init(t_cube3D *data);
void    ft_map_size(t_cube3D *data);
//utility
int     ft_skip_space(char *str);
char    *ft_find_map(int fd);
void	ft_print_struct(t_cube3D data);
void	ft_free_struct(t_cube3D *data);

//check
void    ft_check_map(char **map);
void    ft_check_file(char *file_name);
void    ft_check_info(t_cube3D *data);
void    ft_check_angle(float *angle);

//read_file

void    ft_get_info(t_cube3D *data, int fd);
// char **ft_fill_map(char *str, char **matrix, int fd, char *file_name, t_cube3D *data);
void	ft_fill_map(char *str, int fd, char *file_name, t_cube3D *data);

//movements
int     ft_on(int keycode, t_cube3D *data);
int     ft_off(int keycode, t_cube3D *data);
void    ft_movements(t_cube3D *data);

//draw
void	my_pixel_put(t_img *img, int x, int y, int color);
void    ft_draw_player(t_cube3D *data, int x, int y);
void    ft_draw_cell(t_cube3D *data, int x, int y, int c);
int     ft_draw(t_cube3D *data);
void	drawgri(t_cube3D *data);
void    ft_render_game(t_cube3D *data, t_ray *r);
int		draw_map(int p_w, int p_h, t_cube3D *data);
int		draw(t_cube3D *data, int (*comp)(int, int, t_cube3D *));
int		drawp(t_cube3D *data, int (*comp)(int, int, t_cube3D *,t_ray *),t_ray *r);
int		draw_play(int p_w, int p_h, t_cube3D *data,t_ray *r);



//gnlcube
int	ft_gnlstrlen(const char *str);
int	toomanylines(char *s1, char *s2);
char	*ft_gnlstrjoin(char *s1, char *s2);


#endif



