/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariani <mmariani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 12:39:04 by atarsi            #+#    #+#             */
/*   Updated: 2023/05/10 19:38:19 by mmariani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"

void    ft_render_game(t_cube3D *data, t_ray *r)
{
    float   r_dist = r->dist;
    int     y;
    float   d;
    
    //data->ray.w_x -= 1;
    if(r->dist < 1)
        r->dist = 1;
    r->wall = (data->s_h / 4) / r->dist;

    // printf("%f\n\n\n", r_dist);
    // printf("%f\n", r->wall);
    y = -1;
    while(++y < ((data->s_h /  4) - r->wall))
        my_pixel_put(data, r->w_x, y, COLOR_GREEN);
    y--;
    while(++y < ((data->s_h / 4) + r->wall))
        my_pixel_put(data, r->w_x, y,COLOR_PURPLE);
    y--;
    while(++y < data->s_h)
        my_pixel_put(data, r->w_x, y, COLOR_BLUE);
    //printf("%d\n", data->ray.w_x);
}

void    ft_draw_minimap(t_cube3D *data)
{
    int i = 0;
    int j;
    while (data->map.map[i])
    {
        j = 0;
        while(data->map.map[i][j] != '\0')
        {
            if (data->map.map[i][j] == '1')
                ft_draw_cell(data, j * data->cW_size, i * data->cH_size, 200);
            else
                ft_draw_cell(data, j * data->cW_size, i * data->cH_size, 0);
            j++;
        }
        i++;
    ft_draw_player(data, data->p.x * data->cW_size, data->p.y * data->cH_size);
    //printf("%f\n", data->p.angle);
    // data->minimap.img = mlx_new_image(data->mlx, data->cW_size, data->cH_size);
	// data->minimap.addr = mlx_get_data_addr(data->minimap.img,data->minimap.bfp,data->minimap.l_bytes,data->minimap.endian);

    }
}

void ft_traceray(float rayangle, t_cube3D *data, const int x)
{
    float   cos_ray;
    float   sin_ray;
    t_ray   r;

    r.w_x = x;
    cos_ray = cos(rayangle) / 256;
    sin_ray = sin(rayangle) / 256;
    r.x = data->p.x;
    r.y = data->p.y;

    while(data->map.map[(int)r.y][(int)r.x] != '1' && data->map.map[(int)r.y][(int)r.x] != 'D')
    {
        r.x += cos_ray;
        r.y += sin_ray;
        my_pixel_put(data, (int)(r.x * data->cW_size), (int)(r.y * data->cH_size), 16449536);
    }
    r.dist = sqrt(powf(data->p.x - r.x, 2) + powf(data->p.y - r.y, 2));
    r.dist *= cos((rayangle - data->p.angle)); //ottimizzazone eliminazione fish-eye
    ft_render_game(data, &r);
}

void ft_raycasting(t_cube3D *data)
{
    float   rayangle;
    float   increment;
    int     i;
    float   h_fov;

    data->ray.dist = 0;
    rayangle = data->p.angle - (FOV_R/2);
    //printf("%f\n", rayangle);
    increment = (float)FOV / (float)data->s_w;
    increment *= (PI / 180);
    //printf("%f\n", increment);
    i = 0;
    while(rayangle < data->p.angle + (FOV_R/2))
    {
        ft_traceray(rayangle, data, i);
        rayangle += increment;
        i++;
    }
    //printf("%d\n", i);
    //printf("%d\n\n", data->ray.w_x);
}

int    ft_draw(t_cube3D *data)
{
	static int frame=0;
	frame+=1;
	if(frame%100==0)
	{
		// mlx_clear_window(data->mlx,data->win);
		ft_movements(data);
		ft_raycasting(data);
		ft_draw_minimap(data);
    	mlx_put_image_to_window(data->mlx, data->win, data->minimap.img, 0, 0);
		mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
		mlx_destroy_image(data->mlx,data->img.img);
		mlx_destroy_image(data->mlx,data->minimap.img);
		if(frame>1000)
			frame=0;
	}
	// usleep(10);
    return(0);
}