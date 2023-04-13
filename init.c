/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 15:08:51 by atarsi            #+#    #+#             */
/*   Updated: 2023/04/04 15:34:10 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"

void ft_init_info(t_cube3D *data)
{
    data->NO = NULL;
    data->SO = NULL;
    data->EA = NULL;
    data->WE = NULL;
    data->DO = NULL;
    data->F = -1;
    data->C = -1;
}
