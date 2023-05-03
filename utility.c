/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariani <mmariani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 15:17:22 by atarsi            #+#    #+#             */
/*   Updated: 2023/05/03 18:40:48 by mmariani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"

void ft_map_size(t_cube3D *data)
{
    int row;
    int col;

    row = 0;
    while(data->map.map[row] != NULL)
    {
        col = 0;
        while(data->map.map[row][col] != '\0')
        {
           
            col++;
            if (col > data->widht)
                data->widht = col;
        }
        row++;
    }
    data->height = row;
    //data->widht = col;
    //printf("%d %d %s\n", data->height, data->widht, "DIOCANE");
}

int ft_skip_space(char *str)
{
    int i;

    i = 0;
    while(ft_isspace(str[i]) == 1)
        i++;
    return (i);
}

char *ft_find_map(int fd)
{
    char    *str;
    int     i;

    str = get_next_line(fd);
    while(str != NULL)
    {
        i = 0;
        while(ft_isspace(str[i]) == 1)
            i++;
        if(str[i] == '1')
        {
            
            return (str);
        }
        free(str);
        str = get_next_line(fd);
    }
    ft_error("Map");
    return (0);
}

// void	ft_print_struct(t_cube3D data)
// {
// 	//int	row;

// 	// ft_printf("NO: %s\n", data.NO);
// 	// ft_printf("SO: %s\n", data.SO);
// 	// ft_printf("WE: %s\n", data.WE);
// 	// ft_printf("EA: %s\n", data.EA);
// 	// ft_printf("F: %d\n", data.F);
// 	// ft_printf("C: %d\n", data.C);
// 	// row = 0;
// 	// while (data.map[row] != NULL)
// 	// {
// 	// 	ft_printf("%s\n", data.map[row]);
// 	// 	row++;
// 	// }
// }

void	ft_free_struct(t_cube3D *data)
{
	free(data->NO);
	free(data->SO);
	free(data->WE);
	free(data->EA);
	ft_free_matrix((void **)data->map.map);
}
