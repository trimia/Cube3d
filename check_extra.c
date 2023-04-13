/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_extra.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 16:43:31 by atarsi            #+#    #+#             */
/*   Updated: 2023/04/04 17:53:14 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"

void ft_check_spaces(char **map, int col, int row)
{
    if(map[row - 1][col] == ' ' || map[row - 1][col] == '\0')
        ft_error("Map");
    if(map[row + 1][col] == ' ' || map[row + 1][col] == '\0')
        ft_error("Map");
    if(map[row][col - 1] == ' ' || map[row][col - 1] == '\0')
        ft_error("Map");
    if(map[row][col - 1] == ' ' || map[row][col + 1] == '\0')
        ft_error("Map");
    if(map[row - 1][col - 1] == ' ' || map[row - 1][col - 1] == '\0')
        ft_error("Map");
    if(map[row + 1][col + 1] == ' ' || map[row + 1][col + 1] == '\0')
        ft_error("Map");
    if(map[row - 1][col + 1] == ' ' || map[row - 1][col + 1] == '\0')
        ft_error("Map");
    if(map[row + 1][col - 1] == ' ' || map[row + 1][col - 1] == '\0')
        ft_error("Map");
}

void    ft_check_map(char **map)
{
    int row;
    int col;
    int count;
    char    c;
    
    count = 0;
    row = 0;
    while(map[row] != NULL)
    {
        col = 0;
        while(map[row][col] != '\0')
        {
            c = map[row][col];
            if( c == 'N' || c == 'S' || c == 'W' || c == 'E')
                count++;
            if(c == '0' || c == 'D' || c == 'N' || c == 'S' || c == 'W' || c == 'E')
            {
                ft_check_spaces(map, col, row);
                //printf("%c\n", map[row][col]);
            }
            else if(c == '1' && c == ' ')
                ft_error("Map");
            col++;
        }
        row++;
    }
    if(count != 1)
        ft_error("Map");
}