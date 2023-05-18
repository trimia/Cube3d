/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariani <mmariani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 12:39:04 by atarsi            #+#    #+#             */
/*   Updated: 2023/05/12 16:32:53 by mmariani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"

// void    ft_render_game(t_cube3D *data, t_ray *r)
// {
//     float   r_dist = r->dist;
//     int     y;
//     float   d;
    
//     //data->ray.w_x -= 1;
//     if(r->dist < 1)
//         r->dist = 1;
//     r->wall = (data->s_h * r->dist)/data->s_w;
//     printf("hwall=%f\n",r->wall);
//     y = -1;
//     while(++y < r->wall)
// 		data->img.addr[(int)(y  * (int)data->s_w + r->w_x  )] = HEX_GREEN;
//         // my_pixel_put(&data->img, r->w_x, y, COLOR_GREEN);
//     y--;
//     while(++y < ((data->s_h) + r->wall))
//         my_pixel_put(&data->img, r->w_x, y,COLOR_PURPLE);
//     y--;
//     while(++y < data->s_h)
//         my_pixel_put(&data->img, r->w_x, y, COLOR_SKY);
// }
void    ft_render_game(t_cube3D *data, t_ray *r)
{
    float   r_dist = r->dist;
    int     y;
    float   d;
    
    //data->ray.w_x -= 1;
    r_dist = (data->s_w/2 *1/tan(HALF_FOV))* data->p.angle;
    r_dist *= cos(HALF_FOV); 

    if(r->dist < 1)
        r->dist = 1;
    r->wall = (data->s_h * r->dist)/data->s_w;
    printf("hwall=%f\n",r->wall);
    y = -1;
    while(++y < (data->s_h-(r->wall*64))/2 )
		data->img.addr[(int)(y  * (int)data->s_w + r->w_x  )] = HEX_SKY;
        // my_pixel_put(&data->img, r->w_x, y, COLOR_GREEN);
    y--;
    while(++y < (data->s_h + (r->wall*64))/2)
		data->img.addr[(int)(y  * (int)data->s_w + r->w_x  )] = HEX_PURPLE;
        // my_pixel_put(&data->img, r->w_x, y,COLOR_PURPLE);
    y--;
    while(++y < data->s_h)
		data->img.addr[(int)(y  * (int)data->s_w + r->w_x  )] = HEX_GREEN;
        // my_pixel_put(&data->img, r->w_x, y, COLOR_SKY);
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
		// data->minimap.addr[(int)((r.x*data->cellsize) * (int)data->s_w + (r.y*data->cellsize))] = 0xff0000;
        r.x += cos_ray;
        r.y += sin_ray;
        
        mini_pixel_put(&data->minimap, (int)(r.x * data->cellsize), (int)(r.y * data->cellsize), COLOR_RED);
    }
    r.dist = sqrt(powf(data->p.x - r.x, 2) + powf(data->p.y - r.y, 2));
    // r.dist *= cos((rayangle - data->p.angle)); //ottimizzazone eliminazione fish-eye
    
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
    increment = (float)FOV / (float)data->s_w;
    increment *= (PI / 180);
    i = 0;
    while(rayangle < data->p.angle + (FOV_R/2))
    {
        ft_traceray(rayangle, data, i);
        rayangle += increment;
        i++;
    }
}

int    ft_draw(t_cube3D *data)
{
	static int frame=0;
	// frame+=1;
    
	// if(frame%100==0)
	// if(frame==3)
	// {
		// mlx_clear_window(data->mlx,data->win);
		ft_movements(data);
		// ft_draw_minimap(data);
        draw(data,&draw_map);
		ft_draw_player(data, data->p.x * data->cellsize, data->p.y * data->cellsize);
		ft_raycasting(data);
		mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
    	mlx_put_image_to_window(data->mlx, data->win, data->minimap.img, 0, 0);
		// mlx_destroy_image(data->mlx,data->img.img);
		// mlx_destroy_image(data->mlx,data->minimap.img);
		// mlx_clear_window(data->mlx,data->win);

		// if(frame>3)
			// frame=0;
        
	// }
    // else
        // frame++;
	// usleep(10);
    return(0);
}

int		draw_map(int p_w, int p_h, t_cube3D *data)
{
	int	cur_x;
	int cur_y;

	cur_x = (int)p_w / data->cellsize;
	cur_y = (int)p_h / data->cellsize;
	if (cur_x >= (int)ft_strlen(data->map.map[cur_y]))
		return (0);
	else if (data->map.map[cur_y][cur_x] == '1')
		data->minimap.addr[(int)(p_h * (int)data->map.mm_W + p_w)] = HEX_BLUE;
	else
		data->minimap.addr[(int)(p_h * (int)data->map.mm_W + p_w)] = HEX_BLACK;
	return (1);
}

int		draw(t_cube3D *data, int (*comp)(int, int, t_cube3D *))
{
	int	pixel_w;
	int	pixel_h;

	pixel_h = 0;
	while (pixel_h < data->map.mm_H)
	{
		pixel_w = 0;
		while (pixel_w < data->map.mm_W)
		{
			comp(pixel_w, pixel_h, data);
			pixel_w++;
		}
		pixel_h++;
	}
	return (0);
}

void    ft_draw_player(t_cube3D *data, int x, int y)
{
    int	i;
	int	j;
	int tot;

	i = y-2;
    while(i <= (y +2))
    {
        j = x-2;
        while(j <= (x +2))
        {
    		data->minimap.addr[(int)(i * (int)data->map.mm_W + j)] = HEX_RED;
            j++;
        }
        i++;
    }
}
