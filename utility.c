/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 15:17:22 by atarsi            #+#    #+#             */
/*   Updated: 2023/04/04 17:19:24 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"

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
            return (str);
        free(str);
        str = get_next_line(fd);
    }
    ft_error("Map");
    return (0);
}

void	ft_print_struct(t_cube3D data)
{
	int	row;

	ft_printf("NO: %s\n", data.NO);
	ft_printf("SO: %s\n", data.SO);
	ft_printf("WE: %s\n", data.WE);
	ft_printf("EA: %s\n", data.EA);
	ft_printf("F: %d\n", data.F);
	ft_printf("C: %d\n", data.C);
	row = 0;
	while (data.map[row] != NULL)
	{
		ft_printf("%s\n", data.map[row]);
		row++;
	}
}

void	ft_free_struct(t_cube3D *data)
{
	free(data->NO);
	free(data->SO);
	free(data->WE);
	free(data->EA);
	ft_free_matrix((void **)data->map);
}
