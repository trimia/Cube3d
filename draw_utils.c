/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:07:47 by atarsi            #+#    #+#             */
/*   Updated: 2023/04/22 16:57:18 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"

void	my_pixel_put(t_cube3D *data, int x, int y, int color)
{
	char	*dst;

	dst = data->img.addr + (y * data->img.l_bytes + x * (data->img.bfp / 8));
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
            my_pixel_put(data, x + j, y + i, c);
            j++;
        }
    i++;
    }
}