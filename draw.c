/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariani <mmariani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 12:39:04 by atarsi            #+#    #+#             */
/*   Updated: 2023/05/05 17:45:47 by mmariani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"

// void    ft_render_game(t_cube3D *data)
// {
//     int y = 0;

//     while(y < (data->s_w / 2) - )
//         my_pixel_put(data.)
// }

void    ft_draw_minimap(t_cube3D *data)
{
	int i = 0;
	int j;
	while (data->map.map[i] != NULL)
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
	}
}
void    ft_draw_player(t_cube3D *data, int x, int y)
{
    int	i;
	int	j;
	int tot;

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
void drawwallflorrsky(float rayangle,t_cube3D *data)
{
	float h_wall = data->ray.dist * data->s_h/data->s_w;
	int y ;
	int hit=0;
	// float rayangle = data->p.angle - (FOV_R/2);

	t_ray   r;

	r.x = data->p.x;
	r.y=data->s_h - h_wall/2;
	y= data->s_h - h_wall/2;
	// while (++y < data->s_h-1)
	while (++y < data->s_h/2 - ( (data->s_h/2)/data->ray.dist))
		my_pixel_put(data,  (int)(r.x * 64), y*64,COLOR_BLUE);
	y=-1;
	// while (++y < data->s_w)
	// 	my_pixel_put(data, rayangle, y,COLOR_GREEN);
	// while(hit==0)
	// 	if(data->map.map[(int)data->ray.y][(int)data->ray.x]>0) hit=1;
	// if (hit ==1)
	// {
	// 	while(1)
	// 	{
	// 		while(r.y < h_wall)
	// 		{
	// 			r.x = data->p.x;
	// 			r.y++;
	// 			// printf(" rx=%f ry=%f\n",r.x,r.y);
	// 			my_pixel_put(data, (int)(r.x * data->cW_size), (int)(r.y * data->cH_size), COLOR_PURPLE);
	// 		}
	// 	}
	// }
	
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

	while(data->map.map[(int)r.y][(int)r.x] != '1' && data->map.map[(int)r.y][(int)r.x] != 'D')
	{
		r.x += cos_ray;
		r.y += sin_ray;
		my_pixel_put(data, (int)(r.x * data->cW_size), (int)(r.y * data->cH_size), 16449536);
	}
	drawwallflorrsky(rayangle,data);
	//ft_render_game(data);
}

void ft_raycasting(t_cube3D *data)
{
	float   rayangle;
	float   increment;
	int     i;
	float   h_fov;

	//h_fov = HALF_FOV * (PI/180);
	// printf("%f\n", data->p.angle);
	rayangle = data->p.angle - (FOV_R/2);
	//printf("%f\n", rayangle);
	increment = (float)FOV / (float)data->s_w;
	i = 0;
	while(rayangle < data->p.angle + (FOV_R/2))
	{
		ft_traceray(rayangle, data);
		drawwallflorrsky(rayangle,data);
		rayangle += increment;
		i++;
	}
	data->ray.dist = sqrtf(powf(data->p.x - data->ray.x, 2) + powf(data->p.y - data->ray.y, 2));
	data->ray.dist *= cos((rayangle - data->p.angle));
}

int    ft_draw(t_cube3D *data)
{
	ft_movements(data);
	ft_draw_minimap(data);
	ft_raycasting(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	return(0);
}
