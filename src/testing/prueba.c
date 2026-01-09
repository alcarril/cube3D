
#include "cube3D.h"

void	print_texture_values(t_mlx *mlx)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		printf("Texture %d - width: %d, height: %d, line_length: %d, bits_per_pixel: %d, endian: %d\n",
			i,
			mlx->textures[i].width,
			mlx->textures[i].height,
			mlx->textures[i].line_length,
			mlx->textures[i].bits_per_pixel,
			mlx->textures[i].endian);
		i++;
	}
}

