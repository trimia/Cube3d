/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariani <mmariani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 18:36:35 by mmariani          #+#    #+#             */
/*   Updated: 2023/05/04 15:18:56 by mmariani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"


void cast(t_cube3D *data)
{
	data->s_w;	//dim schermo x
	data->s_h;	//dim schermo y
	data->p.x;	//pos x player
	data->p.y;	//pos y player

	int cell_x = data->p.x >> 6; //is like dividere per 64 2^6	
	int cell_y = data->p.y >> 6;
	
}










































void	background(t_cube3D *data)
{
	int	x;
	int	y;

	y = -1;
	while (++y < data->s_h)
	{
		x = -1;
		while (++x < data->s_w)
		{
			if (y < (data->s_h / 2))
				data->raycast.buf[x][y] = data->map.ceiling_color;
			else
				data->raycast.buf[y][x] = data->map.floor_color;
		}
	}
}

void	init_math(t_math *math, t_game *game, int x)
{
	math->camera_x = 2 * x / (double)W_WIDTH - 1;
	math->ray_dir_x = game->player.dir_x + game->player.plane_x
		* math->camera_x;
	math->ray_dir_y = game->player.dir_y + game->player.plane_y
		* math->camera_x;
	math->map_x = (int)game->player.pos_x;
	math->map_y = (int)game->player.pos_y;
	math->delta_dist_x = fabs(1 / math->ray_dir_x);
	math->delta_dist_y = fabs(1 / math->ray_dir_y);
	math->hit = 0;
}

//Digital Differential Analysis
void	dda(t_math *math, t_game *game)
{
	while (math->hit == 0)
	{
		if (math->side_dist_x < math->side_dist_y)
		{
			math->side_dist_x += math->delta_dist_x;
			math->map_x += math->step_x;
			math->side = 0;
		}
		else
		{
			math->side_dist_y += math->delta_dist_y;
			math->map_y += math->step_y;
			math->side = 1;
		}
		if (game->map.map_int[math->map_x][math->map_y] > 0)
			math->hit = 1;
	}
}

	// ft_bzero(&math, sizeof(t_math));
void	wall_cast(t_game *game)
{
	t_math	math;
	int		x;
	int		y;

	x = -1;
	while (++x < W_WIDTH)
	{
		init_math(&math, game, x);
		step_side(&math, game);
		dda(&math, game);
		distance_ray(&math, game);
		calculate_pixel(&math, game);
		y = math.draw_start ;
		while (y < math.draw_end)
		{
			math.tex_y = (int)math.tex_pos & (TEXTURE_SIZE - 1);
			math.tex_pos += math.step;
			math.color = game->text[math.tex_n]
			[TEXTURE_SIZE * math.tex_y + math.tex_x];
			game->buff[y][x] = math.color;
			y++;
		}
	}
}

void	ray_cast(t_cube3D *data)
{
	background(data);
	wall_cast(data);
}


void floor_casting(t_cube3D *data)
{
    int y;
    int x;
    float rayDirX0;
	float rayDirY0;
	float rayDirX1;
	float rayDirY1;
	
	data->raycast.plane.x = 0.0;
	data->raycast.plane.y = 0.66;
    

    y = 0;
    x = 0;
    while(y < data->s_h )
    {
		rayDirX0 = data->ray.x - data->raycast.plane.x;
		rayDirY0 = data->ray.y - data->raycast.plane.y;
		rayDirX1 = data->ray.x + data->raycast.plane.x;
		rayDirY1 = data->ray.y + data->raycast.plane.y;
		// Current y position compared to the center of the screen (the horizon)
		int p = y - data->s_h / 2;

		// Vertical position of the camera.
		float posZ = 0.5 * data->s_h;

		// Horizontal distance from the camera to the floor for the current row.
		// 0.5 is the z position exactly in the middle between floor and ceiling.
		float rowDistance = posZ / p;

		// calculate the real world step vector we have to add for each x (parallel to camera plane)
		// adding step by step avoids multiplications with a weight in the inner loop
		float floorStepX = rowDistance * (rayDirX1 - rayDirX0) / data->s_w;
		float floorStepY = rowDistance * (rayDirY1 - rayDirY0) / data->s_w;

		// real world coordinates of the leftmost column. This will be updated as we step to the right.
		float floorX = data->p.x + rowDistance * rayDirX0;
		float floorY = data->p.y + rowDistance * rayDirY0;
		
		while(x < data->s_h)
		{
			// the cell coord is simply got from the integer parts of floorX and floorY
			int cellX = (int)(floorX);
			int cellY = (int)(floorY);

			// get the texture coordinate from the fractional part
			int tx = (int)(texWidth * (floorX - cellX)) & (texWidth - 1);
			int ty = (int)(texHeight * (floorY - cellY)) & (texHeight - 1);

			floorX += floorStepX;
			floorY += floorStepY;

			// choose texture and draw the pixel
			int floorTexture = 3;
			int ceilingTexture = 6;

			int color;

			// floor
			color = data->raycast.texture[floorTexture][texWidth * ty + tx];
			color = (color >> 1) & 8355711; // make a bit darker

			data->raycast.buf[y][x] = color;

			//ceiling (symmetrical, at screenHeight - y - 1 instead of y)
			color = data->raycast.texture[ceilingTexture][texWidth * ty + tx];
			color = (color >> 1) & 8355711; // make a bit darker

			data->raycast.buf[data->s_h - y - 1][x] = color;
			x++;
		}
        y++;
    }
}
void wall_casting(t_cube3D *data)
{
	
}

void	calc(t_info *info)
{
	//FLOOR CASTING
	for(int y = 0; y < height; y++)
	{
		// rayDir for leftmost ray (x = 0) and rightmost ray (x = w)
		float rayDirX0 = info->dirX - info->planeX;
		float rayDirY0 = info->dirY - info->planeY;
		float rayDirX1 = info->dirX + info->planeX;
		float rayDirY1 = info->dirY + info->planeY;

		// Current y position compared to the center of the screen (the horizon)
		int p = y - height / 2;

		// Vertical position of the camera.
		float posZ = 0.5 * height;

		// Horizontal distance from the camera to the floor for the current row.
		// 0.5 is the z position exactly in the middle between floor and ceiling.
		float rowDistance = posZ / p;

		// calculate the real world step vector we have to add for each x (parallel to camera plane)
		// adding step by step avoids multiplications with a weight in the inner loop
		float floorStepX = rowDistance * (rayDirX1 - rayDirX0) / width;
		float floorStepY = rowDistance * (rayDirY1 - rayDirY0) / width;

		// real world coordinates of the leftmost column. This will be updated as we step to the right.
		float floorX = info->posX + rowDistance * rayDirX0;
		float floorY = info->posY + rowDistance * rayDirY0;

		for(int x = 0; x < width; ++x)
		{
			// the cell coord is simply got from the integer parts of floorX and floorY
			int cellX = (int)(floorX);
			int cellY = (int)(floorY);

			// get the texture coordinate from the fractional part
			int tx = (int)(texWidth * (floorX - cellX)) & (texWidth - 1);
			int ty = (int)(texHeight * (floorY - cellY)) & (texHeight - 1);

			floorX += floorStepX;
			floorY += floorStepY;

			// choose texture and draw the pixel
			int floorTexture = 3;
			int ceilingTexture = 6;

			int color;

			// floor
			color = info->texture[floorTexture][texWidth * ty + tx];
			color = (color >> 1) & 8355711; // make a bit darker

			info->buf[y][x] = color;

			//ceiling (symmetrical, at screenHeight - y - 1 instead of y)
			color = info->texture[ceilingTexture][texWidth * ty + tx];
			color = (color >> 1) & 8355711; // make a bit darker

			info->buf[ - y - 1][x] = color;
		}
	}
	//WALL CASTING
	for(int x = 0; x < width; x++)
	{
		double cameraX = 2 * x / (double)width - 1;
		double rayDirX = info->dirX + info->planeX * cameraX;
		double rayDirY = info->dirY + info->planeY * cameraX;
		
		int mapX = (int)info->posX;
		int mapY = (int)info->posY;

		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;
		
		 //length of ray from one x or y-side to next x or y-side
		double deltaDistX = fabs(1 / rayDirX);
		double deltaDistY = fabs(1 / rayDirY);
		double perpWallDist;
		
		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;
		
		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?

		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (info->posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - info->posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (info->posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - info->posY) * deltaDistY;
		}

		while (hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			//Check if ray has hit a wall
			if (worldMap[mapX][mapY] > 0) hit = 1;
		}
		if (side == 0)
			perpWallDist = (mapX - info->posX + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - info->posY + (1 - stepY) / 2) / rayDirY;

		//Calculate height of line to draw on screen
		int lineHeight = (int)(height / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + height / 2;
		if(drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + height / 2;
		if(drawEnd >= height)
			drawEnd = height - 1;

		// texturing calculations
		int texNum = worldMap[mapX][mapY] - 1;

		// calculate value of wallX
		double wallX;
		if (side == 0)
			wallX = info->posY + perpWallDist * rayDirY;
		else
			wallX = info->posX + perpWallDist * rayDirX;
		wallX -= floor(wallX);

		// x coordinate on the texture
		int texX = (int)(wallX * (double)texWidth);
		if (side == 0 && rayDirX > 0)
			texX = texWidth - texX - 1;
		if (side == 1 && rayDirY < 0)
			texX = texWidth - texX - 1;

		// How much to increase the texture coordinate perscreen pixel
		double step = 1.0 * texHeight / lineHeight;

		// Starting texture coordinate
		double texPos = (drawStart - height / 2 + lineHeight / 2) * step;

		for (int y = drawStart; y < drawEnd; y++)
		{
			// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
			int texY = (int)texPos & (texHeight - 1);
			texPos += step;

			int color = info->texture[texNum][texHeight * texY + texX];

			// make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
			if (side == 1)
				color = (color >> 1) & 8355711;

			info->buf[y][x] = color;
		}

		//FLOOR CASTING (vertical version, directly after drawing the vertical wall stripe for the current x)
		double floorXWall, floorYWall; //x, y position of the floor texel at the bottom of the wall

		//4 different wall directions possible
		if(side == 0 && rayDirX > 0)
		{
			floorXWall = mapX;
			floorYWall = mapY + wallX;
		}
		else if(side == 0 && rayDirX < 0)
		{
			floorXWall = mapX + 1.0;
			floorYWall = mapY + wallX;
		}
		else if(side == 1 && rayDirY > 0)
		{
			floorXWall = mapX + wallX;
			floorYWall = mapY;
		}
		else
		{
			floorXWall = mapX + wallX;
			floorYWall = mapY + 1.0;
		}

		double distWall, distPlayer, currentDist;

		distWall = perpWallDist;
		distPlayer = 0.0;

		if (drawEnd < 0) drawEnd = height; //becomes < 0 when the integer overflows

		//draw the floor from drawEnd to the bottom of the screen
		for(int y = drawEnd + 1; y < height; y++)
		{
			currentDist = height / (2.0 * y - height); //you could make a small lookup table for this instead

			double weight = (currentDist - distPlayer) / (distWall - distPlayer);

			double currentFloorX = weight * floorXWall + (1.0 - weight) * info->posX;
			double currentFloorY = weight * floorYWall + (1.0 - weight) * info->posY;

			int floorTexX, floorTexY;
			floorTexX = (int)(currentFloorX * texWidth) % texWidth;
			floorTexY = (int)(currentFloorY * texHeight) % texHeight;

			int checkerBoardPattern = ((int)(currentFloorX) + (int)(currentFloorY)) % 2;
			int floorTexture;
			if(checkerBoardPattern == 0) floorTexture = 3;
			else floorTexture = 4;

			//floor
			info->buf[y][x] = (info->texture[floorTexture][texWidth * floorTexY + floorTexX] >> 1) & 8355711;
			//ceiling (symmetrical!)
			info->buf[height - y][x] = info->texture[6][texWidth * floorTexY + floorTexX];
		}
	}
}