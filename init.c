/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariani <mmariani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 15:08:51 by atarsi            #+#    #+#             */
/*   Updated: 2023/05/10 19:41:14 by mmariani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"

void    ft_init_image(t_cube3D *data)
{
    data->map.mm_H = data->s_h / 2;
    data->map.mm_W = data->s_w / 2;
    data->cH_size = (data->map.mm_H / 3 / data->height);
    data->cW_size = (data->map.mm_W / data->widht);
    data->img.img = mlx_new_image(data->mlx, data->s_w, data->s_h);
    data->minimap.img = mlx_new_image(data->mlx, 200, 500);
    data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bfp, &data->img.l_bytes, &data->img.endian);
	data->minimap.addr = mlx_get_data_addr(data->minimap.img, &data->minimap.bfp, &data->minimap.l_bytes, &data->minimap.endian);
}

void ft_init_info(t_cube3D *data)
{
    data->NO = NULL;
    data->SO = NULL;
    data->EA = NULL;
    data->WE = NULL;
    data->DO = NULL;
    data->F = -1;
    data->C = -1;
}

void    ft_init_player(t_cube3D *data, char c)
{
    if(c == 'S')
        data->p.angle = PI/2;
    else if(c == 'E')
        data->p.angle = 0;
    else if(c == 'W')
        data->p.angle = PI;
    else if(c == 'N')
        data->p.angle = (3 * PI)/2;
    //printf("%f\n", data->p.angle);
}

void ft_find_p(t_cube3D *data)
{
    char c;
    int row;
    int col;

    row = 0;
    while(data->map.map[row] != NULL)
    {
        col = 0;
        while(data->map.map[row][col] != '\0')
        {
            c = data->map.map[row][col];
            if(c == 'N' || c == 'S' || c == 'W' || c == 'E')
            {
                ft_init_player(data, c);
                data->p.x = col + 0.5;
                data->p.y = row + 0.5;
            }
            //printf("%d %d %d\n", data->height, data->widht, col);
            col++;
        }
        row++;
    }
}

void    ft_init(t_cube3D *data)
{
    ft_find_p(data);
    data->p.w = 0;
    data->p.a = 0;
    data->p.s = 0;
    data->p.d = 0;
    // data->mini_cell_h = 0;
    // data->mini_cell_w = 0;
    data->ray.w_x = 0;
    data->p.rigth = 0;
    data->p.left = 0;
    data->cH_size = 0;
    data->cW_size = 0;
    data->map.mm_H = 0;
    data->map.mm_W = 0;
    data->p.dx = cos(data->p.angle);
    data->p.dy = sin(data->p.angle);
    data->mlx = mlx_init();
    mlx_get_screen_size(data->mlx, &data->s_h, &data->s_w);
    // data->s_h=HEIGHT;
    // data->s_w=WEIGHT;
    printf("%d %d\n", data->s_h, data->s_w);
    data->win = mlx_new_window(data->mlx, data->s_w, data->s_h, "cub3D");
    ft_init_image(data);
}