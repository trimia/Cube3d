/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariani <mmariani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 14:15:25 by atarsi            #+#    #+#             */
/*   Updated: 2023/04/13 16:36:07 by mmariani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

#include "libft/libft.h"
#include "minilibx/mlx.h"
// #include "minilibx_mms_20200219/mlx.h"
#define PI 3.14159265359
#define RAD 0.0174533

typedef struct s_player
{

    int rigth;
    int left;
}              t_player;

typedef struct s_cube3D
{
    char    *NO;
    char    *SO;
    char    *WE;
    char    *EA;
    char    *DO;
    int     F;
    int     C;
    int     height;
    int     widht;
    int     s_h;
    int     s_w;
    void    *mlx;
    void    *win;
    char    **map;
    //t_text  text[5];
    //t_player    p;
    int     frame;
}               t_cube3D;


//init

void ft_init_info(t_cube3D *data);
//utility
int ft_skip_space(char *str);
char *ft_find_map(int fd);
void	ft_print_struct(t_cube3D data);
void	ft_free_struct(t_cube3D *data);

//check
void    ft_check_map(char **map);
void ft_check_file(char *file_name);
void ft_check_info(t_cube3D *data);
//read_file

void    ft_get_info(t_cube3D *data, int fd);
char **ft_fill_map(char *str, char **matrix, int fd, char *file_name);

//movements
int	ft_on(int keycode, t_cube3D *data);
int ft_off(int keycode, t_cube3D *data);

#endif
