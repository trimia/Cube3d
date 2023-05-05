/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariani <mmariani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 15:14:13 by atarsi            #+#    #+#             */
/*   Updated: 2023/05/05 15:41:55 by mmariani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"

char *ft_fill_info(char *str)
{
	char    *tmp;
	int     i;
	int     j;

	i = 0;
	while(ft_isspace(str[i]) == 1)
		i++;
	j = 0;
	while(ft_isspace(str[i + j]) == 0)
		j++;
	str[i + j] = '\0';
	tmp = (char *) malloc (sizeof(char) * (j + 1));
	ft_check_malloc(tmp);
	j = 0;
	while(str[i + j] != '\0')
	{
		tmp[j] = str[i + j];
		j++;
	}
	tmp[j] = '\0';
	return (tmp);
}

int ft_parse_info(t_cube3D *data, char *str)
{   
	if(ft_memcmp(str, "NO", 2) == 0 && data->NO == NULL)
	 data->NO = ft_fill_info(str + 2);
	else if(ft_memcmp(str, "SO", 2) == 0 && data->SO == NULL)
		data->SO = ft_fill_info(str + 2);
	else if(ft_memcmp(str, "WE", 2) == 0 && data->WE == NULL)
		data->WE = ft_fill_info(str + 2);
	else if(ft_memcmp(str, "EA", 2) == 0 && data->EA == NULL)
		data->EA = ft_fill_info(str + 2);
	// else if(ft_memcmp(str, "DO", 2) == 0 && data->DO == NULL)
	//     data->DO = ft_fill_info(str + 2);
	else if(*str == 'F' && data->F == -1)
	   data->F = 1;
	else if(*str == 'C' && data->C == -1)
	   data->C = 1;	
	else
		return(0);
	return (1);        
}

void    ft_get_info(t_cube3D *data, int fd)
{
	char    *str;
	int     i;

	i = 0;
	str = get_next_line(fd);
	while(str != NULL)
	{
		i = ft_skip_space(str);
		if (str[i] == '1')
		{
			free(str);
			break ;
		}
		if (str[i] != '\0')
			if(ft_parse_info(data, str + i) == 0)
				ft_error("info");
		free(str);
		str = get_next_line(fd);
	}
}

void	ft_fill_map(char *str, int fd, char *file_name, t_cube3D *data)
{
	int i;
	char *matrix;

	i = 0;
	while (str != NULL)
	{
		i++;
		free(str);
		str = get_next_line(fd);
	}
	close(fd);
	matrix = ft_calloc(1, 1);
	fd = open(file_name, O_RDONLY);
	str = ft_find_map(fd);
	while(str != NULL)
	{
		matrix = ft_gnlstrjoin(matrix, str);
		free(str);
		str = get_next_line(fd);
		printf("%s", str); //				printf
	}
	data->map.map=ft_split(matrix,'\n');
	
	close(fd);
}
