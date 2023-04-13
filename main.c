/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariani <mmariani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 14:40:08 by atarsi            #+#    #+#             */
/*   Updated: 2023/04/13 16:00:02 by mmariani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"

void    ft_read_file(char *file_name, t_cube3D *data)
{
    int     fd;
    //int     i;
    char    *str;
    char    **matrix = NULL;

    ft_init_info(data);
    fd = open(file_name, O_RDONLY);
    ft_get_info(data, fd);
    ft_check_info(data);
    close(fd);
    fd = open(file_name, O_RDONLY);
    str = ft_find_map(fd);
    data->map = ft_fill_map(str, matrix, fd, file_name);
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
    //ft_print_struct(data);
    data.mlx = mlx_init();
    mlx_get_screen_size(data.mlx,&data.s_h,&data.s_w);
    // mlx_get_screen_size(data.mlx, &data.s_h, &data.s_w);
    data.win = mlx_new_window(data.mlx, data.s_w, data.s_h, "cub3D");
    //mlx_put_image_to_window(data.mlx, data.win, NULL, 0, 0);
    //mlx_do_key_autorepeaton(data.mlx);
	//mlx_hook(data.win, 2, 0, ft_on, &data);
	//mlx_hook(data.win, 3, 0, ft_off, &data);
	//mlx_loop_hook(data.mlx, ft_display, &data);
	mlx_loop(data.mlx);
	//ft_free_struct(&data);
    
    return (0);
}