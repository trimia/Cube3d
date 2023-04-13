/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 14:49:06 by atarsi            #+#    #+#             */
/*   Updated: 2023/04/04 17:43:07 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"

void    ft_check_fd(char *file_name, char *str)
{
    int fd;

    fd = open(file_name, O_RDONLY);
    if(fd <= 0)
    {
        ft_printf("%s ", str);
        ft_error("file");
    }
    close(fd);
}

void ft_check_file(char *file_name)
{
    if(ft_strlen(file_name) < 5)
        ft_error("Map name");
    if(ft_memcmp(&file_name[ft_strlen(file_name) - 4], ".cub", 4) != 0)
        ft_error("Map extencion");
    ft_check_fd(file_name, "Map");
}

void ft_check_info(t_cube3D *data)
{
    if(data->NO == NULL || data->SO == NULL || data->WE == NULL)
        ft_error("Info");
    if(data->EA == NULL || data->C < 0 || data->F < 0)
        ft_error("Info");
    // ft_check_fd(data->NO, "Texture1");
    // ft_check_fd(data->SO, "Texture2");
    // ft_check_fd(data->WE, "Texture3");
    // ft_check_fd(data->EA, "Texture4");
    // if(data->DO)
    //     ft_check_fd(data->DO, "Texture");
}