/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariani <mmariani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:07:47 by atarsi            #+#    #+#             */
/*   Updated: 2023/05/10 19:13:31 by mmariani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"

void	my_pixel_put(t_cube3D *data, int x, int y, int color)
{
	char	*dst;

	dst = data->img.addr + (y * data->img.l_bytes + x * (data->img.bfp / 8));
	*(unsigned int *)dst = color;
}
void	my_mini_pixel_put(t_cube3D *data, int x, int y, int color)
{
	char	*dst;

	dst = data->minimap.addr + (y * data->minimap.l_bytes + x * (data->minimap.bfp / 8));
	*(unsigned int *)dst = color;
}


void ft_draw_cell(t_cube3D *data, int x, int y, int c)
{
    int i;
    int j;

    i = 0;
    while(i < data->cH_size)
    {
        j = 0;
        while(j < data->cW_size)
        {
            my_mini_pixel_put(data, x + j, y + i, c);
            j++;
        }
    i++;
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
            my_mini_pixel_put(data, (int)j, (int)i, 16449536);
            j++;
        }
        i++;
    }
}