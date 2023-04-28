/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 12:22:55 by atarsi            #+#    #+#             */
/*   Updated: 2023/04/24 17:58:45 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"

void ft_move(float m_x, float m_y, t_cube3D *data)
{
    float   i;
    
    i = (data->p.x + m_x);
    if (data->map[(int)data->p.y][(int)i] != '1')
        data->p.x += m_x;
    i = (data->p.y + m_y);
    if (data->map[(int)i][(int)data->p.x] != '1')
        data->p.y += m_y;
}

int ft_on(int keycode, t_cube3D *data)
{
    if (keycode == ESC)
        exit(0);
    if (keycode == W)
        data->p.w = 1;
    if (keycode == A)
        data->p.a = 1;
    if (keycode == S)
        data->p.s = 1;
    if (keycode == D)
        data->p.d = 1;
    if (keycode == LEFT)
        data->p.left = 1;
    if (keycode == RIGHT)
        data->p.rigth = 1;
    return (0);
}

int ft_off(int keycode, t_cube3D *data)
{
    if (keycode == ESC)
        exit(0);
    if (keycode == W)
        data->p.w = 0;
    if (keycode == A)
        data->p.a = 0;
    if (keycode == S)
        data->p.s = 0;
    if (keycode == D)
        data->p.d = 0;
    if (keycode == LEFT)
        data->p.left = 0;
    if (keycode == RIGHT)
        data->p.rigth = 0;
    return (0);
}

void    ft_dir(t_cube3D *data, float dir)
{
    data->p.angle += dir;
    ft_check_angle(&data->p.angle);
    data->p.dx = cos(data->p.angle);
    data->p.dy = sin(data->p.angle);
}

void ft_movements(t_cube3D *data)
{
    float   langle;
    float   ldx;
    float   ldy;

    langle = data->p.angle - PI/2;
    ft_check_angle(&langle);
    ldx = cos(langle);
    ldy = sin(langle);
    if (data->p.w == 1)
        ft_move(data->p.dx * SPEED, data->p.dy * SPEED, data);
    if (data->p.a == 1)
        ft_move(ldx * SPEED, ldy * SPEED, data);
    if (data->p.s == 1)
        ft_move(-(data->p.dx * SPEED), -(data->p.dy * SPEED), data);
    if (data->p.d == 1)
        ft_move(-(ldx * SPEED), -(ldy * SPEED), data);
    if (data->p.left == 1)
        ft_dir(data, -ROT);
    if (data->p.rigth == 1)
        ft_dir(data, ROT);
}