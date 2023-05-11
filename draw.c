/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariani <mmariani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 12:39:04 by atarsi            #+#    #+#             */
/*   Updated: 2023/05/11 17:48:25 by mmariani         ###   ########.fr       */
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
        my_pixel_put(&data->img, r->w_x, y, COLOR_GREEN);
    y--;
    while(++y < ((data->s_h / 4) + r->wall))
        my_pixel_put(&data->img, r->w_x, y,COLOR_PURPLE);
    y--;
    while(++y < data->s_h)
        my_pixel_put(&data->img, r->w_x, y, COLOR_BLUE);
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
                // ft_draw_cell(data, j * data->cW_size, i * data->cH_size, 200);
            // else
                // ft_draw_cell(data, j * data->cW_size, i * data->cH_size, 0);
            j++;
        }
        i++;
    // ft_draw_player(data, data->p.x * data->cW_size, data->p.y * data->cH_size);
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
		// data->minimap.addr[(int)(r.x * (int)data->s_w + r.y)] = 0xff0000;
        
        // my_pixel_put(&data->minimap, (int)(r.x * data->cW_size), (int)(r.y * data->cH_size), 16449536);
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
	// frame+=1;
    
	// if(frame%100==0)
	// if(frame==3)
	// {
		// mlx_clear_window(data->mlx,data->win);
		ft_movements(data);
		ft_raycasting(data);
		// ft_draw_minimap(data);
        draw(data,&draw_map);
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
		data->minimap.addr[(int)(p_h * (int)data->map.mm_W + p_w)] = 0x0000ff;
	else
		data->minimap.addr[(int)(p_h * (int)data->map.mm_W + p_w)] = 0x7a7a7a;
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
    		// data->minimap.addr[(int)(data->p.x  *(int)data->map.mm_W + data->p.y * pixel_h)] = 0xff0000;
			pixel_w++;
		}
		pixel_h++;
	}
    		// data->minimap.addr[(int)(data->p.x * (int)data->map.mm_W + data->p.y)] = 0xff0000;
    
    // ft_draw_player(data, data->p.x * data->cellsize, data->p.y * data->cellsize);
    // ft_draw_player(data, data->p.x, data->p.y);

	return (0);
}



// void    ft_draw_player(t_cube3D *data, int x, int y)
// {
//     int	i;
// 	int	j;
// 	int tot;

// 	i = 0;
//     while(i < data->map.mm_H)
//     {
//         j = 0;
//         while(j < data->map.mm_W)
//         {
//     		data->minimap.addr[(int)(j * (int)data->map.mm_W + i)] = 0xff0000;

//             // my_pixel_put(&data->minimap, (int)j, (int)i, 16449536);
//             j++;
//         }
//         i++;
//     }
// }


void    ft_draw_player(t_cube3D *data, int x, int y)
{
    int	i;
	int	j;
	int tot;

	i = y - data->cellsize;
    while(i <= (y + (data->cellsize>>8)))
    {
        j = x - data->cellsize;
        while(j <= (x + (data->cellsize>>8)))
        {
    		data->minimap.addr[(int)(j * (int)data->map.mm_W + i)] = 0xff0000;

            // my_pixel_put(data, (int)j, (int)i, 16449536);
            j++;
        }
        i++;
    }
}