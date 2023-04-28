/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariani <mmariani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 14:40:08 by atarsi            #+#    #+#             */
/*   Updated: 2023/04/28 14:47:05 by mmariani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"

void    ft_read_file(char *file_name, t_cube3D *data)
{
    int     fd;
    char    *str;

    data->height = 0;
    data->widht = 0;
    ft_init_info(data);
    fd = open(file_name, O_RDONLY);
    ft_get_info(data, fd);
    ft_check_info(data);
    close(fd);
    fd = open(file_name, O_RDONLY);
    str = ft_find_map(fd);
    ft_fill_map(str, fd, file_name, data);
    ft_map_size(data);
    printf("%d %d\n", data->height, data->widht);
    ft_check_map(data->map);

    close(fd);
}

int main(int argc, char *argv[])
{
    t_cube3D data;

    if(argc != 2)
        ft_error("Arg");
    ft_check_file(argv[1]);
    ft_read_file(argv[1], &data);
    ft_init(&data);
	mlx_hook(data.win, 2, 0, ft_on, &data);
	mlx_hook(data.win, 3, 0, ft_off, &data);
	mlx_loop_hook(data.mlx, ft_draw, &data);
    //printf("    %f     %f\n", data.p.x, data.p.y);
    mlx_loop(data.mlx);
	//ft_free_struct(&data);
    return (0);
}