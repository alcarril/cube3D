
#include "cube3D.h"

void	print_texture_values(t_mlx *mlx)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		printf("Texture %d - width: %d, height: %d, line_length: %d, bits_per_pixel: %d, endian: %d, image %p\n",
			i,
			mlx->map->textures[i].width,
			mlx->map->textures[i].height,
			mlx->map->textures[i].line_length,
			mlx->map->textures[i].bits_per_pixel,
			mlx->map->textures[i].endian, mlx->map->textures[i].img);
		i++;
	}
}

