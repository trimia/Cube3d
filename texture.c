/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariani <mmariani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:54:42 by mmariani          #+#    #+#             */
/*   Updated: 2023/05/10 18:57:50 by mmariani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


//carica img e riempe le texture dalle xpm forse vanno allocate
void	load_image(t_info *info, int *texture, char *path, t_img *img) 
{
	img->img = mlx_xpm_file_to_image(info->mlx, path, &img->img_width, &img->img_height);
	img->data = (int *)mlx_get_data_addr(img->img, &img->bpp, &img->size_l, &img->endian);
	for (int y = 0; y < img->img_height; y++)
	{
		for (int x = 0; x < img->img_width; x++)
		{
			texture[img->img_width * y + x] = img->data[img->img_width * y + x];
		}
	}
	mlx_destroy_image(info->mlx, img->img);
}
//carica singole texture ho preso quelle che ho trovato sul lsample di minilibx
void	load_texture(t_info *info)
{
	t_img	img;

	load_image(info, info->texture[0], "textures/eagle.xpm", &img);
	load_image(info, info->texture[1], "textures/redbrick.xpm", &img);
	load_image(info, info->texture[2], "textures/purplestone.xpm", &img);
	load_image(info, info->texture[3], "textures/greystone.xpm", &img);
	load_image(info, info->texture[4], "textures/bluestone.xpm", &img);
	load_image(info, info->texture[5], "textures/mossy.xpm", &img);
	load_image(info, info->texture[6], "textures/wood.xpm", &img);
	load_image(info, info->texture[7], "textures/colorstone.xpm", &img);
}
//funzione che ritorna il colore delle texture da passare a put pixel
unsigned int	get_color(t_image *tex, int x, int y, t_rules *rules)
{
	if (!(x < 0 || x > rules->mlx.win_width - 1
			|| y < 0 || y > rules->mlx.win_height - 1))
	{
		return (*(unsigned int *)(tex->addr + (4 * (tex->width * y + x)))); //non capisco perche moltiplica per 4
	
	}
	return (0x0);
}
//funzione che ritorna il colore letto da f e c "conversione da rgb a unsigned int" l'ultimo credo sia il canale alpha
unsigned int	get_color_arr(unsigned char arr[3])
{
	return (*(unsigned int *)(unsigned char [4]){arr[2], arr[1], arr[0], 0});
}