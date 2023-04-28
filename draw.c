/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariani <mmariani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 12:39:04 by atarsi            #+#    #+#             */
/*   Updated: 2023/04/28 16:54:38 by mmariani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"

void    ft_draw_player(t_cube3D *data, int x, int y)
{
    int	i;
	int	j;
	// int tot;

	i = y - data->cW_size / 8;
    while(i <= (y + data->cW_size / 8))
    {
        j = x - data->cH_size / 8;
        while(j <= (x + data->cH_size / 8))
        {
            my_pixel_put(data, (int)j, (int)i, 16449536);
            j++;
        }
        i++;
    }
}

void    ft_draw_minimap(t_cube3D *data)
{
    int i = 0;
    int j;
    while (data->map[i] != NULL)
    {
        j = 0;
        while(data->map[i][j] != '\0')
        {
            if (data->map[i][j] == '1')
                ft_draw_cell(data, j * data->cW_size, i * data->cH_size, 200);
            else
                ft_draw_cell(data, j * data->cW_size, i * data->cH_size, 0);
            j++;
        }
        i++;
    ft_draw_player(data, data->p.x * data->cW_size, data->p.y * data->cH_size);
    //printf("%f\n", data->p.angle);
    mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
    }
}

void ft_traceray(float rayangle, t_cube3D *data)
{
    float   cos_ray;
    float   sin_ray;
    t_ray   r;

    //rayangle *= (PI/180);
    cos_ray = cos(rayangle) / 256;
    sin_ray = sin(rayangle) / 256;
    r.x = data->p.x;
    r.y = data->p.y;

    while(data->map[(int)r.y][(int)r.x] != '1' && data->map[(int)r.y][(int)r.x] != 'D')
    {
        r.x += cos_ray;
        r.y += sin_ray;
        my_pixel_put(data, (int)(r.x * data->cW_size), (int)(r.y * data->cH_size), 16449536);
    }
}

void ft_raycasting(t_cube3D *data)
{
    float   rayangle;
    float   increment;
    int     i;
    // float   h_fov;

    //h_fov = HALF_FOV * (PI/180);
    // printf("%f\n", data->p.angle);
    rayangle = data->p.angle - (FOV_R/2);
    printf("%f\n", rayangle);
    increment = (float)FOV / (float)data->s_w;
    i = 0;
    while(rayangle < data->p.angle + (FOV_R/2))
    {
        ft_traceray(rayangle, data);
        rayangle += increment;
        i++;
    }
}

int    ft_draw(t_cube3D *data)
{
    ft_movements(data);
    ft_draw_minimap(data);
    // ft_raycasting(data);
    mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
    return(0);
}